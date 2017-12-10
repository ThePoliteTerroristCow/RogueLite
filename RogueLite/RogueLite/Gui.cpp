#include <stdio.h>
#include <stdarg.h>
#include <string>
#include "Main.h"

Gui::Gui() {
	cheatsCon = new TCODConsole((engine.screenWidth - 2) - ui.cheats.CHEAT_WIDTH, ui.cheats.CHEAT_TOP);
	healthCon = new TCODConsole(engine.screenWidth, ui.health.HEALTH_TOP);
	msgCon = new TCODConsole(engine.screenWidth, 4);
}

Gui::~Gui() {
	delete healthCon;
	delete cheatsCon;
	delete msgCon;
	log.clearAndDelete();
}

Gui::Message::Message(const char *text, const TCODColor &col) : text(_strdup(text)), col(col) {}
Gui::Message::~Message() { free(text); }

//////////////////////////////////////////////////////////////////////////

void Gui::clearMsgCon() {
	msgCon->clear();
	log.clear();
	ui.msgVars.bClearOnTurn = false;
}

void Gui::message(const TCODColor &col, bool clearOnTurn, const char *text ...) {
	ui.msgVars.bClearOnTurn = clearOnTurn;
	va_list ap;
	char buf[256];
	va_start(ap, text);
	vsprintf(buf, text, ap);
	va_end(ap);

	char *lineBegin = buf;
	char *lineEnd;
	do {
		// make room for the new message
		if (log.size() == 1) {
			Message *toRemove = log.get(0);
			log.remove(toRemove);
			delete toRemove;
		}

		// detect end of the line
		lineEnd = strchr(lineBegin, '\n');
		if (lineEnd) {
			*lineEnd = '\0';
		}
		// add a new message to the log
		Message *msg = new Message(lineBegin, col);
		log.push(msg);
		// go to next line
		lineBegin = lineEnd + 1;
	} while (lineEnd);
}

void Gui::render() {
	// draw the health UI
	healthCon->setDefaultBackground(TCODColor::black);
	healthCon->clear();
	renderHealthBar(1, 1, ui.health.HEALTH_WIDTH, ui.health.HEALTH_NAME, engine.player->destructible->currentHp, engine.player->destructible->maxHp, TCODColor::lightRed, TCODColor::darkerRed);
	TCODConsole::blit(healthCon, 0, 0, engine.screenWidth, ui.health.HEALTH_TOP, TCODConsole::root, 0, engine.screenHeight - ui.health.HEALTH_TOP);

	// draw the messages UI
	if (bSetMsgBoxXY == false) setMsgBoxXY();
	msgCon->setDefaultBackground(TCODColor::black);
	msgCon->clear();
	renderMsgBox(1, 1, ui.msgFrame.MSG_WIDTH, ui.msgFrame.MSG_HEIGHT);
	if (ui.msgVars.bRenderMouseInfo == true) renderMouseLook();
	TCODConsole::blit(msgCon, 0, 0, ui.msgFrame.MSG_WIDTH, ui.msgFrame.MSG_HEIGHT, TCODConsole::root, ui.msgFrame.MSG_LEFTX, ui.msgFrame.MSG_TOP);

	// draw the cheats UI
	if (cheats.sv.cheatsEnabled == true) {
		cheatsCon->setDefaultBackground(TCODColor::black);
		cheatsCon->clear();
		renderCheatBar(1, 1, ui.cheats.CHEAT_WIDTH, ui.cheats.CHEAT_NAME, TCODColor::darkGrey);
		TCODConsole::blit(cheatsCon, 0, 0, engine.screenWidth, ui.cheats.CHEAT_TOP, TCODConsole::root, (engine.screenWidth - 2) - ui.cheats.CHEAT_WIDTH, engine.screenHeight - ui.cheats.CHEAT_TOP);
	}
}

//////////////////////////////////////////////////////////////////////////

void Gui::renderCheatBar(int x, int y, int width, const char *name, const TCODColor &backColor) {
	cheatsCon->setDefaultBackground(backColor);
	cheatsCon->rect(x, y, width, ui.cheats.CHEAT_HEIGHT, false, TCOD_BKGND_SET);

	cheatsCon->setDefaultForeground(TCODColor::white);
	cheatsCon->printEx(x, y, TCOD_BKGND_NONE, TCOD_LEFT, "%s", name);
	if (cheats.sv.showPlayerPos == true) {
		cheatsCon->printEx(x, y + 1, TCOD_BKGND_NONE, TCOD_LEFT, "Player X: %i", engine.player->x);
		cheatsCon->printEx(x, y + 2, TCOD_BKGND_NONE, TCOD_LEFT, "Player Y: %i", engine.player->y);
	}
	if (cheats.sv.fovCheat == true) cheatsCon->printEx(x, y + 3, TCOD_BKGND_NONE, TCOD_LEFT, "FOV: %i", fov.currentFov);
	if (cheats.sv.renderCheat == true) cheatsCon->printEx(x, y + 4, TCOD_BKGND_NONE, TCOD_LEFT, "MAP VIS: ON");
	if (cheats.sv.bGodmode == true) cheatsCon->printEx(x, y + 5, TCOD_BKGND_NONE, TCOD_LEFT, "GODMODE: ON");
}

void Gui::renderHealthBar(int x, int y, int width, const char *name, float value, float maxValue, const TCODColor &barColor, const TCODColor &backColor) {
	healthCon->setDefaultBackground(backColor);
	healthCon->rect(x, y, width, 1, false, TCOD_BKGND_SET);
	int barWidth = (int)(value / maxValue * width);
	if (barWidth > 0) {
		// draw the bar
		healthCon->setDefaultBackground(barColor);
		healthCon->rect(x, y, barWidth, 1, false, TCOD_BKGND_SET);
	}
	// print text on top of the bar
	healthCon->setDefaultForeground(TCODColor::white);
	healthCon->printEx(x, y, TCOD_BKGND_NONE, TCOD_LEFT, "%s: %g/%g", name, value, maxValue);
	healthCon->printEx(x, y + 1, TCOD_BKGND_NONE, TCOD_LEFT, "FPS: %f", engine.fFrameRate);
}

void Gui::renderMouseLook() {
	if (!engine.map->isInFov(engine.mouse.cx, engine.mouse.cy)) {
		// do not print anything mouse is out of fov
		return;
	}

	std::string strName;
	for (Actor **iterator = engine.actors.begin(); iterator != engine.actors.end(); iterator++) {
		Actor *actor = *iterator;
		if (actor->x == engine.mouse.cx && actor->y == engine.mouse.cy) {
			// discard if hovering over player
			if (actor == engine.player) return;

			// check if actor is a container
			if (actor->container) {
				strName = actor->name;
				msgCon->setDefaultForeground(TCODColor::white);
				msgCon->clear();
				msgCon->printRect(1, 1, ui.msgFrame.MSG_WIDTH, ui.msgFrame.MSG_HEIGHT, strName.c_str());
				return;
			}
			// check if actor is lootable
			if (actor->lootable) {
				strName = actor->name;
				msgCon->setDefaultForeground(TCODColor::white);
				msgCon->clear();
				msgCon->printRect(1, 1, ui.msgFrame.MSG_WIDTH, ui.msgFrame.MSG_HEIGHT, strName.c_str());
				return;
			}

			// check if actor is dead
			if (actor->destructible->isDead()) {
				std::string strCorpseName = actor->destructible->corpseName;
				msgCon->clear();
				msgCon->printRect(1, 1, ui.msgFrame.MSG_WIDTH, ui.msgFrame.MSG_HEIGHT, strCorpseName.c_str());
				return;
			}

			// truncate any floating points 
			int truncCurrentHP = (int)(100 * actor->destructible->currentHp) / 100.0;
			int truncMaxHP = (int)(100 * actor->destructible->maxHp) / 100.0;
			int truncATK = (int)(100 * actor->attacker->power) / 100.0;
			int truncDEF = (int)(100 * actor->destructible->defense) / 100.0;

			// store & append actor attributes
			strName = actor->name;
			strName.append(":\nHP: ");
			strName.append(std::to_string(truncCurrentHP));
			strName.append("/");
			strName.append(std::to_string(truncMaxHP));
			strName.append("\nATK: ");
			strName.append(std::to_string(truncATK));
			strName.append(" | DEF: ");
			strName.append(std::to_string(truncDEF));
		}
	}
	// print the results
	msgCon->setDefaultForeground(TCODColor::lightGrey);
	msgCon->printRect(1, 1, ui.msgFrame.MSG_WIDTH, ui.msgFrame.MSG_HEIGHT, strName.c_str());
}

void Gui::renderMsgBox(int x, int y, int width, int height) {
	TCODColor &backColor = TCODConsole::root->getDefaultBackground();
	msgCon->setDefaultBackground(backColor);

	// draw the message log
	int msgLine = 1;
	float colorCoef = 0.4f;
	for (Message **it = log.begin(); it != log.end(); it++) {
		Message *message = *it;
		msgCon->setDefaultForeground(message->col * colorCoef);
		msgCon->printRect(x, y, width, height, message->text);
		msgLine++;
		if (colorCoef < 1.0f) {
			colorCoef += 0.3f;
		}
	}
}

void Gui::setMsgBoxXY() {
	bSetMsgBoxXY = true;
	const int x1 = engine.screenWidth - ui.cheats.CHEAT_WIDTH - 2;
	const int x2 = engine.screenWidth - ui.health.HEALTH_WIDTH - 1;
	ui.msgFrame.MSG_TOP = engine.screenHeight - ui.health.HEALTH_TOP;
	ui.msgFrame.MSG_HEIGHT = (engine.screenHeight + ui.cheats.CHEAT_HEIGHT) - engine.screenHeight;
	ui.msgFrame.MSG_LEFTX = ui.health.HEALTH_WIDTH + 1;
	ui.msgFrame.MSG_WIDTH = (x1 + x2) - engine.screenWidth;
}

