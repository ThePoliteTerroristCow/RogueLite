#include <stdio.h>
#include <stdarg.h>
#include "Main.h"

static const int MSG_X = 1;
static const int MSG_HEIGHT = 4;

Gui::Gui() {
	cheatsCon = new TCODConsole((engine.screenWidth - 2) - ui.cheats.CHEAT_WIDTH, ui.cheats.CHEAT_TOP);
	healthCon = new TCODConsole(engine.screenWidth, ui.health.HEALTH_TOP);
	msgCon = new TCODConsole(engine.screenWidth, MSG_HEIGHT);
}

Gui::~Gui() {
	delete healthCon;
	delete cheatsCon;
	delete msgCon;
	log.clearAndDelete();
}

Gui::Message::Message(const char *text, const TCODColor &col) :
	col(col) {
	this->text = new char[strlen(text)];
	strcpy(this->text, text);
}
Gui::Message::~Message() {
	delete[] text;
}

//////////////////////////////////////////////////////////////////////////

void Gui::message(const TCODColor &col, const char *text, ...) {
	va_list ap;
	char buf[256];
	va_start(ap, text);
	vsprintf(buf, text, ap);
	va_end(ap);

	char *lineBegin = buf;
	char *lineEnd;

	do {
		// make room for the new message
		if (log.size() == MSG_HEIGHT) {
			Message *toRemove = log.get(0);
			log.remove(toRemove);
//			delete toRemove;
		}
		// detect manually declared end of line
		lineEnd = strchr(lineBegin, '\n');
		if (lineEnd) {
			*lineEnd = '\0';
		}
		// add a new message to the log
		Message *msg = new Message(lineBegin, col);
		log.push(msg);
		// go to the next line
		lineBegin = lineEnd + 1;
	} while (lineEnd);
}

void Gui::render() {
	// draw the health UI
	healthCon->setDefaultBackground(TCODColor::black);
	healthCon->clear();
	renderHealthBar(1, 1, ui.health.HEALTH_WIDTH, ui.health.HEALTH_NAME, engine.player->destructible->currentHp, engine.player->destructible->maxHp, TCODColor::lightRed, TCODColor::darkerRed);
	TCODConsole::blit(healthCon, 0, 0, engine.screenWidth, ui.health.HEALTH_TOP, TCODConsole::root, 0, engine.screenHeight - ui.health.HEALTH_TOP);

	// draw the cheats UI
	if (cheats.sv.cheatsEnabled == true) {
		cheatsCon->setDefaultBackground(TCODColor::black);
		cheatsCon->clear();
		renderCheatBar(1, 1, ui.cheats.CHEAT_WIDTH, ui.cheats.CHEAT_NAME, TCODColor::darkGrey);
		TCODConsole::blit(cheatsCon, 0, 0, engine.screenWidth, ui.cheats.CHEAT_TOP, TCODConsole::root, (engine.screenWidth - 2) - ui.cheats.CHEAT_WIDTH, engine.screenHeight - ui.cheats.CHEAT_TOP);
	}

	// draw the messages UI
	//msgCon->setDefaultBackground(TCODColor::black);
	//msgCon->clear();
	//renderMsgBox(1, 1, engine.screenWidth, true, TCODColor::black);
	//TCODConsole::blit(msgCon, 0, 0, engine.screenWidth, 3, TCODConsole::root, 0, 1);
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
}

void Gui::renderMsgBox(int x, int y, int width, bool centerText, const TCODColor &backColor) {
	int currentLine = 1;
	float colorCoef = 0.4f;
	msgCon->setDefaultBackground(backColor);
	for (Message **it = log.begin(); it != log.end(); it++) {
		Message *message = *it;
		msgCon->setDefaultForeground(message->col * colorCoef);
		msgCon->setDefaultBackground(message->col);
		if (centerText == true || centerText == false) { // change this later obviously
			msgCon->print(MSG_X, currentLine, message->text);
		}
		currentLine++;
		if (colorCoef < 1.0f) {
			colorCoef += 0.3f;
		}
	}
}

//////////////////////////////////////////////////////////////////////////

