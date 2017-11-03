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
		void spawnNewDungeon(); // unacceptable method (creates a new process, closes current), but for now it works
	} sv;

protected:
	void storeFov();
	int storedFov;
};

extern FOV fov;