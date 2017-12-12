#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include "Main.h"

//////////////////////////////////////////////////////////////////////////
// PLAYER AI

void PlayerAi::handleActionKey(Actor *owner, int ascii) {
	switch (ascii) {
	// Movement Keys
	case 'w': inputY = -1; break;
	case 's': inputY = +1; break;
	case 'a': inputX = -1; break;
	case 'd': inputX = +1; break;

	// Pickup Items Key
	case 'e':
	{
		// TESTING //
		engine.parser->readAudioCfg();
		engine.parser->readGraphicsCfg();

		bool found = false;
		for (Actor **iterator = engine.actors.begin(); iterator != engine.actors.end(); iterator++) {
			Actor *actor = *iterator;
			if (actor->lootable) {
				if (actor->x == engine.player->x && actor->x == engine.player->y) {
					if (actor->lootable->loot(actor, owner)) {
						found = true;
						engine.gui->message(TCODColor::lightGrey, true, "You pick up the %s.", actor->name);
						break;
					}
					else if (!found) {
						found = true;
						engine.gui->message(TCODColor::red, true, "Your inventory is full!");
					}
				}
			}
		}
		if (found == false) {
			engine.gui->message(TCODColor::lightGrey, true, "You search the area but find nothing.");
		}
		//engine.gameStatus = Engine::NEW_TURN; // un-comment will make loot checks take a turn
	}
	default:break;
	}
}

void PlayerAi::handleActionKeys() {	
	// Mouse Events
	if (engine.mouse.rbutton_pressed) {
		if (engine.gui->ui.msgVars.bRenderMouseInfo == true) engine.gui->ui.msgVars.bRenderMouseInfo = false;
		else engine.gui->ui.msgVars.bRenderMouseInfo = true;
	}

	// Fullscreen toggle
	if (engine.lastKey.vk == TCODK_ENTER && engine.lastKey.lalt) {
		if (TCODConsole::isFullscreen() == false) TCODConsole::setFullscreen(true);
		else TCODConsole::setFullscreen(false);
	}
	if (engine.lastKey.vk == TCODK_ESCAPE) { if (TCODConsole::isFullscreen() == true) { TCODConsole::setFullscreen(false); } }

// DEBUGGING / CHEATS
	// Godmode
	if (engine.lastKey.c == 'i' && engine.lastKey.rctrl && engine.lastKey.ralt && cheats.sv.cheatsEnabled == 1) {
		if (cheats.sv.bGodmode == true) cheats.sv.bGodmode = false;
		else {
			cheats.sv.bGodmode = true;
			cheats.setMaxHealth(engine.player);
		}
	}

	// Noclip toggle
	if (engine.lastKey.c == 'n' && engine.lastKey.rctrl && engine.lastKey.ralt && cheats.sv.cheatsEnabled == 1) {
		if (cheats.sv.bNoclip == true) {
			cheats.sv.bNoclip = false;
			printf("Noclip disabled\n");
		}
		else {
			cheats.sv.bNoclip = true;
			printf("Noclip enabled\n");
		}
	}

	// Restart Application
	if (engine.lastKey.c == 'r' && engine.lastKey.rctrl && engine.lastKey.ralt && cheats.sv.cheatsEnabled == 1) {
		cheats.restartApp(NULL);
	}

	// Cheats toggle
	if (engine.lastKey.vk == TCODK_1 && engine.lastKey.rctrl && engine.lastKey.ralt) {
		if (cheats.sv.cheatsEnabled == true)
		{
			cheats.sv.cheatsEnabled = false;
			cheats.sv.fovCheat = false;
			cheats.sv.renderCheat = false;
			cheats.sv.showPlayerPos = false;
			cheats.sv.bGodmode = false;
			cheats.sv.bNoclip = false;
		}
		else if (cheats.sv.cheatsEnabled == false) {
			cheats.sv.cheatsEnabled = true;
			cheats.sv.showPlayerPos = true;
		}
	}

	// Add to FOV
	if (engine.lastKey.vk == TCODK_2 && engine.lastKey.rctrl && engine.lastKey.ralt) {
		if (cheats.sv.cheatsEnabled == true)
		{
			cheats.sv.fovCheat = true;
			fov.setFov(fov.currentFov - 1);
			engine.map->computeFov();
		}
	}

	// Subtract from FOV
	if (engine.lastKey.vk == TCODK_3 && engine.lastKey.rctrl && engine.lastKey.ralt) {
		if (cheats.sv.cheatsEnabled == true)
		{
			cheats.sv.fovCheat = true;
			fov.setFov(fov.currentFov + 1);
			engine.map->computeFov();
		}
	}

	// Toggle Render Cheat
	if (engine.lastKey.vk == TCODK_4 && engine.lastKey.rctrl && engine.lastKey.ralt) {
		if (cheats.sv.cheatsEnabled == true)
		{
			if (cheats.sv.renderCheat == true) {
				cheats.sv.renderCheat = false;
				engine.map->renderCheat();
			}
			else if (cheats.sv.renderCheat == false) {
				cheats.sv.renderCheat = true;
			}
		}
	}

	// Spawn a new random dungeon 
	if (cheats.sv.cheatsEnabled == true && engine.lastKey.vk == TCODK_5 && engine.lastKey.rctrl && engine.lastKey.ralt) {
		cheats.spawnNewDungeon(engine.map->width, engine.map->height);
	}
}

// Handles the player controller & all associated logic
void PlayerAi::update(Actor *owner) {
	if (owner->destructible && owner->destructible->isDead()) {
		return;
	}
	inputX = 0, inputY = 0;
	switch (engine.lastKey.vk) {
	case TCODK_CHAR: handleActionKey(owner, engine.lastKey.c); break;

	// ***WRAP THESE UP IN A FUNCTION FOR LATER***
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

			// ***Temporary message fix!*** 
			// Refer to 'Gui.h' for details on the turnCount & clearMsgCon bug
			if (engine.gui->ui.msgVars.bClearOnTurn == true) {
				if (engine.gui->ui.msgVars.turnCount != 0) --engine.gui->ui.msgVars.turnCount;
				else {
					engine.gui->ui.msgVars.turnCount = 0; // Setting this to 1 instead of 0 will cause all messages to clear 1 move after we want
					engine.gui->clearMsgCon();
				}
			}
		}
	}

	// Check for multi key-presses
	handleActionKeys();
}

bool PlayerAi::moveOrAttack(Actor *owner, int targetX, int targetY) {
	// Force ourselves forwards if noclip is enabled
	if (cheats.sv.bNoclip == true) {
		if (engine.map->isWall(targetX, targetY)) {
			owner->x = targetX;
			owner->y = targetY;
			return true;
		}
	}

	if (engine.map->isWall(targetX, targetY)) return false;
	// look for living actors to attack
	for (Actor **iterator = engine.actors.begin(); iterator != engine.actors.end(); iterator++) {
		Actor *actor = *iterator;
		bool corpseOrItem = (actor->destructible && actor->destructible->isDead()) || actor->lootable;
		if (actor->destructible && !actor->destructible->isDead() && actor->x == targetX && actor->y == targetY) {
			owner->attacker->attack(owner, actor);
			return false;
		}
		if (corpseOrItem && actor->x == targetX && actor->y == targetY) {
			// Setting 'turnCount' here temporarily fixes the buggy message clearing until I can properly look at it
			engine.gui->ui.msgVars.turnCount = 1;
			engine.gui->message(TCODColor::lightGrey, true, "There is a %s here.", actor->name);
			// Instead of displaying a message, use this space to update a console that displays objects that 
			// are on the ground in our player's current position. Then text can be moved to its own dedicated area.
			// Doing this should also fix the bug that is tied to 'turnCount' & 'clearMsgCon' 
		}
	}

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