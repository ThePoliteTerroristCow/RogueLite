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
	engine.player->destructible->currentHp = engine.player->destructible->maxHp;
	engine.actors.clear();
	engine.map->map->clear(true, true);
	engine.map->generateNewDungeon(x, y);

	// Places the player into the nearest room if spawned inside a wall
	int playerX = engine.player->x;
	int playerY = engine.player->y;
	if (!engine.map->canWalk(playerX, playerY)) {
		for (int iX = playerX; iX < x; iX++) {
			for (int iY = playerY; iY < y; iY++) {
				if (engine.map->canWalk(iX, iY)) {
					engine.player->x = iX;
					engine.player->y = iY;
				}
				else if (iX > x || iY > y) {
					// no rooms found; spawn us at 0,0 and try again
					playerX = 0;
					playerY = 0;
				}
			}
		}
	}

	// Make sure all actors are placed inside the walls
	for (Actor **iterator = actors.begin(); iterator != actors.end(); iterator++) {
		Actor *actor = *iterator;
		if (actor != engine.player) {
			if (!engine.map->canWalk(actor->x, actor->y)) {
				for (int aiX = actor->x; aiX < actor->x; aiX++) {
					for (int aiY = actor->y; aiY < actor->y; aiY++) {
						if (engine.map->canWalk(aiX, aiY)) {
							actor->x = aiX;
							actor->y = aiY;
						}
						else if (aiX >= actor->x || aiY >= actor->y && engine.map->canWalk(aiX, aiY) == false) {
							// find a way to clear this actor instance. in the meantime, spawn them off-screen and kill them
						}
					}
				}
			}
		}
	}
	updateEngine();
}

void Cheats::updateEngine() {
	engine.map->computeFov();
	engine.update();
	engine.render();
}

