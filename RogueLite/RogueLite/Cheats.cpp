#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include "Main.h"

void Cheats::restartApp(char *processName) {
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));
	si.cb = sizeof(si);

	if (processName == NULL || strlen(processName) <= 0) {
		TCHAR szExeFileName[MAX_PATH];
		GetModuleFileName(NULL, szExeFileName, MAX_PATH);
		if (szExeFileName != NULL) {
			processName = szExeFileName;
		}
		else {
			processName = rogueLiteName;
		}
	}

	if (!CreateProcessA(processName, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		printf("Error restarting process!\n");
	}
	else ExitProcess(0);
}

void Cheats::setMaxHealth(Actor *owner) {
	owner->destructible->currentHp = owner->destructible->maxHp;
}

void Cheats::spawnNewDungeon(int x, int y) {
	engine.actors.clear();
	engine.map->generateNewDungeon(x, y);
	cheats.setMaxHealth(engine.player);
	updateEngine();
}

void Cheats::updateEngine() {
	engine.map->computeFov();
	engine.update();
	engine.render();
}

