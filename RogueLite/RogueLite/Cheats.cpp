#include <stdio.h>
#include <Windows.h>
#include "Main.h"

void Cheats::restartApp(char *ProcessName) {
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));
	si.cb = sizeof(si);

	if (!CreateProcessA(ProcessName, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		printf("Error re-starting process!\n");
	}
	else ExitProcess(0);
}

void Cheats::spawnNewDungeon(int x, int y) {
	engine.actors.clear();
	engine.map->map->clear(true, false);
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
					engine.player->render();
				}
			}
		}
	}
	engine.gameStatus = Engine::STARTUP;
	updateEngine();
}

void Cheats::updateEngine() {
	engine.update();
	engine.render();
}

