#pragma once

class FOV {
public:
	int currentFov;

	FOV();
	~FOV();

	int getCurrentFov();
	int getStoredFov();
	int setFov(int newFov);

	struct CheatStatus {
	public:
		bool cheatsEnabled = false;
		bool fovCheat = false;
		bool renderCheat = false;
		bool showPlayerPos = false;
		void restart();
		void spawnNewDungeon(int x, int y); // A bit mangled perhaps, but its much cleaner than before
	} sv;

protected:
	int storedFov;

	void updateEngine();
	void storeFov();
};

extern FOV fov;