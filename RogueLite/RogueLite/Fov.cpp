#include "Main.h"

FOV::FOV()
{}

FOV::~FOV()
{}

int FOV::getCurrentFov() {
	return currentFov;
}

int FOV::getStoredFov() {
	return storedFov;
}

int FOV::setFov(int newFov) {
	if (newFov < 0) newFov = 0;
	if (newFov > 99) newFov = 0;
	storedFov = currentFov;
	currentFov = newFov;
	return currentFov;
}

void FOV::storeFov() {
	storedFov = currentFov;
}