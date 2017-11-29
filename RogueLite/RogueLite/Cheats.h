#pragma once

class Cheats {
public:
	TCODList<Actor *> actors; // List of all Actors on the map

	struct CheatStatus {
	public:
		bool cheatsEnabled = false;
		bool fovCheat = false;
		bool bGodmode = false;
		bool bNoclip = false;
		bool renderCheat = false;
		bool showPlayerPos = false;
	} sv;

	// Takes one of two arguments: 
	// - [char] processName: Name of the process to restart
	// - NULL: Attempts to restart the currently running exe
	void setMaxHealth(Actor *owner);
	void restartApp(char *processName);
	void spawnNewDungeon(int x, int y);

protected:
	char *rogueLiteName = "RogueLite.exe";
	void updateEngine();
};

extern Cheats cheats;