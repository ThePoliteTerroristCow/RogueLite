#pragma once

class FOV {
public:
	int currentFov;

	FOV();
	~FOV();

	int getCurrentFov();
	int getStoredFov();
	int setFov(int newFov);

protected:
	void storeFov();
	int storedFov;
};

extern FOV fov;