#pragma once

class Gui {
public:
	Gui();
	~Gui();

	struct uiData {
		struct uiCheats {
			int CHEAT_TOP = 7; // Where the top-most part of the UI starts
			int CHEAT_HEIGHT = 5; // The total height of the UI Element 
			int CHEAT_WIDTH = 20; // The total width of the UI Element 
			const char *CHEAT_NAME = "-- Cheats Enabled --";
		}cheats;

		struct uiHealth {
			int HEALTH_TOP = 7;
			int HEALTH_WIDTH = 20;
			const char *HEALTH_NAME = "HP";
		}health;
	}ui;

	void render();

protected:
	TCODConsole *healthCon;
	TCODConsole *cheatsCon;
	void renderHealthBar(int x, int y, int width, const char *name, float value, float maxValue, const TCODColor &barColor, const TCODColor &backColor);
	void renderCheatBar(int x, int y, int width, const char *name, const TCODColor &backColor);
};