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
	storeFov();
	currentFov = newFov;
	return currentFov;
}

void FOV::storeFov() {
	storedFov = currentFov;
}