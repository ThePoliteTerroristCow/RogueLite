#pragma once

class Cheats {
public:
	struct CheatStatus {
	public:
		bool cheatsEnabled = false;
		bool fovCheat = false;
		bool renderCheat = false;
		bool showPlayerPos = false;
	} sv;

	void restartApp(char *ProcessName);
	void spawnNewDungeon(int x, int y);

protected:
	void updateEngine();
};

extern Cheats cheats;