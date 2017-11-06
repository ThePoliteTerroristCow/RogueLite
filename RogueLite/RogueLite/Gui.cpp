#include "Main.h"

Gui::Gui() {
	healthCon = new TCODConsole(engine.screenWidth, ui.health.HEALTH_TOP);
	cheatsCon = new TCODConsole((engine.screenWidth - 2) - ui.cheats.CHEAT_WIDTH, ui.cheats.CHEAT_TOP);
}

Gui::~Gui() {
	delete healthCon;
	delete cheatsCon;
}

//////////////////////////////////////////////////////////////////////////

void Gui::render() {
	healthCon->setDefaultBackground(TCODColor::black);
	healthCon->clear();
	renderHealthBar(1, 1, ui.health.HEALTH_WIDTH, ui.health.HEALTH_NAME, engine.player->destructible->currentHp, engine.player->destructible->maxHp, TCODColor::lightRed, TCODColor::darkerRed);
	TCODConsole::blit(healthCon, 0, 0, engine.screenWidth, ui.health.HEALTH_TOP, TCODConsole::root, 0, engine.screenHeight - ui.health.HEALTH_TOP);

	if (cheats.sv.cheatsEnabled == true) {
		cheatsCon->setDefaultBackground(TCODColor::black);
		cheatsCon->clear();
		renderCheatBar(1, 1, ui.cheats.CHEAT_WIDTH, ui.cheats.CHEAT_NAME, TCODColor::darkGrey);
		TCODConsole::blit(cheatsCon, 0, 0, engine.screenWidth, ui.cheats.CHEAT_TOP, TCODConsole::root, (engine.screenWidth - 2) - ui.cheats.CHEAT_WIDTH, engine.screenHeight - ui.cheats.CHEAT_TOP);
	}
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