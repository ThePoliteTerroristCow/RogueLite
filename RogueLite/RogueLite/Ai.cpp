#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include "Main.h"

//////////////////////////////////////////////////////////////////////////
// PLAYER AI

// Player movement & keypress checks. Also checks if you're dead to prevent your corpse from wandering.
void PlayerAi::update(Actor *owner) {
	if (owner->destructible && owner->destructible->isDead()) {
		return;
	}
	int inputX = 0, inputY = 0;
	switch (engine.lastKey.vk) {
	case TCODK_UP: inputY = -1; break;
	case TCODK_DOWN: inputY = +1; break;
	case TCODK_LEFT: inputX = -1; break;
	case TCODK_RIGHT: inputX = +1; break;
	default:break;
	}
	if (inputX != 0 || inputY != 0) {
		engine.gameStatus = Engine::NEW_TURN;
		if (moveOrAttack(owner, owner->x + inputX, owner->y + inputY)) {
			engine.map->computeFov();
		}
	}

	// Other combined/misc keypresses go here
	if (engine.lastKey.vk == TCODK_ENTER && engine.lastKey.lalt) TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
	if (engine.lastKey.vk == TCODK_ESCAPE) { if (TCODConsole::isFullscreen()) { TCODConsole::setFullscreen(false); } }

	// DEBUGGING / CHEATS
	if (engine.lastKey.vk == TCODK_ESCAPE && cheats.sv.cheatsEnabled == 1) ExitProcess(0);
	if (engine.lastKey.c == 'r' && engine.lastKey.rctrl && engine.lastKey.ralt && cheats.sv.cheatsEnabled == 1) cheats.restartApp("RogueLite.exe");
	if (engine.lastKey.vk == TCODK_1 && engine.lastKey.rctrl && engine.lastKey.ralt) {
		if (cheats.sv.cheatsEnabled == true)
		{
			cheats.sv.cheatsEnabled = false;
			cheats.sv.fovCheat = false;
			cheats.sv.renderCheat = false;
			cheats.sv.showPlayerPos = false;
		}
		else if (cheats.sv.cheatsEnabled == false) {
			cheats.sv.cheatsEnabled = true;
			cheats.sv.showPlayerPos = true;
		}
	}
	if (engine.lastKey.vk == TCODK_2 && engine.lastKey.rctrl && engine.lastKey.ralt) {
		if (cheats.sv.cheatsEnabled == true)
		{
			cheats.sv.fovCheat = true;
			fov.setFov(fov.currentFov - 1);
			engine.map->computeFov();
		}
	}
	if (engine.lastKey.vk == TCODK_3 && engine.lastKey.rctrl && engine.lastKey.ralt) {
		if (cheats.sv.cheatsEnabled == true)
		{
			cheats.sv.fovCheat = true;
			fov.setFov(fov.currentFov + 1);
			engine.map->computeFov();
		}
	}
	if (engine.lastKey.vk == TCODK_4 && engine.lastKey.rctrl && engine.lastKey.ralt) {
		if (cheats.sv.cheatsEnabled == true)
		{
			if (cheats.sv.renderCheat == true) {
				cheats.sv.renderCheat = false;
			}
			else if (cheats.sv.renderCheat == false) {
				cheats.sv.renderCheat = true;
			}
		}
	}
	if (cheats.sv.cheatsEnabled == true && engine.lastKey.vk == TCODK_5 && engine.lastKey.rctrl && engine.lastKey.ralt) {
		cheats.spawnNewDungeon(80, 43);
	}
}

bool PlayerAi::moveOrAttack(Actor *owner, int targetX, int targetY) {
	if (engine.map->isWall(targetX, targetY)) return false;
	// look for living actors to attack
	for (Actor **iterator = engine.actors.begin(); iterator != engine.actors.end(); iterator++) {
		Actor *actor = *iterator;
		if (actor->destructible && !actor->destructible->isDead() && actor->x == targetX && actor->y == targetY) {
			owner->attacker->attack(owner, actor);
			return false;
		}
	}
	// look for corpses
	for (Actor **iterator = engine.actors.begin(); iterator != engine.actors.end(); iterator++) {
		Actor *actor = *iterator;
		if (actor->destructible && actor->destructible->isDead() && actor->x == targetX && actor->y == targetY) {
			printf("There's a %s here\n", actor->name);
		}
	}
	// return true to update the field of view
	owner->x = targetX;
	owner->y = targetY;
	return true;
}

//////////////////////////////////////////////////////////////////////////
// MONSTER AI

void MonsterAi::moveOrAttack(Actor *owner, int targetX, int targetY) {
	int dirX = targetX - owner->x;
	int dirY = targetY - owner->y;
	int stepDirX = (dirX > 0 ? 1 : -1); // if (dirX > 0) stepDirX = 1; | else stepDirX = -1;
	int stepDirY = (dirY > 0 ? 1 : -1);
	float distance = sqrtf(dirX*dirX + dirY*dirY);

	// Take the monster->player vector and normalize it (divide by its length so that its length is 1), then round 
	// its x,y component to get an integer deplacement vector. The possible return values for dirX,dirY are -1.0 and 1
	if (distance >= 2) {
		dirX = (int)(round(dirX / distance));
		dirY = (int)(round(dirY / distance));
		if (engine.map->canWalk(owner->x + dirX, owner->y + dirY)) {
			owner->x += dirX;
			owner->y += dirY;
		}
		else if (engine.map->canWalk(owner->x + stepDirX, owner->y)) {
			owner->x += stepDirX;
		}
		else if (engine.map->canWalk(owner->x, owner->y + stepDirY)) {
			owner->y += stepDirY;
		}
	}
	else if (owner->attacker) {
		owner->attacker->attack(owner, engine.player);
	}
}

void MonsterAi::update(Actor *owner) {
	if (owner->destructible && owner->destructible->isDead()) {
		return;
	}
	if (engine.map->isInFov(owner->x, owner->y)) {
		// we can see the player & can move towards him
		moveCount = TRACKING_TURNS;
	} 
	else moveCount--;
	
	if (moveCount > 0) {
		moveOrAttack(owner, engine.player->x, engine.player->y);
	}
}