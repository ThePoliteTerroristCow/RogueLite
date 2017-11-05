#include <stdio.h>
#include <Windows.h>
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

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void FOV::updateEngine() {
	engine.update();
	engine.render();
}

void FOV::CheatStatus::restart() {
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));
	si.cb = sizeof(si);

	if (!CreateProcessA("RogueLite.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		printf("Error starting process!\n");
	}
	else ExitProcess(0);
}

void FOV::CheatStatus::spawnNewDungeon(int x, int y) {
	engine.actors.clear();
	engine.map->map->clear(true, false);
	engine.map->generateNewDungeon(x, y);
	engine.gameStatus = Engine::STARTUP;
	engine.update();
	engine.render();
}