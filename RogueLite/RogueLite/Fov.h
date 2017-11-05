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
	int storedFov;
	void storeFov();
};

extern FOV fov;