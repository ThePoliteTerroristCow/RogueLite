#include "stdafx.h"

// CONSTRUCTOR 
Engine::Engine() : gameStatus(STARTUP), fovRadius(FOV_RADIUS) {
	TCODConsole::initRoot(80, 50, MAINCON_TITLE, false);
	player = new Actor(0, 0, '@', "Player", TCODColor::white);
	actors.push(player);
	map = new Map(80, 50);
}

// DESTRUCTOR
Engine::~Engine() {
	actors.clearAndDelete();
	delete map;
}

// Handles the player walking code
void Engine::update() {
	TCOD_key_t key;
	if (gameStatus == STARTUP) map->computeFov();
	gameStatus = IDLE;

	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
	int inputX = 0, inputY = 0;
	switch (key.vk) {
	case TCODK_UP: inputY = -1; break;
	case TCODK_DOWN: inputY = 1; break;
	case TCODK_LEFT: inputX = -1; break;
	case TCODK_RIGHT: inputX = 1; break;
	default: break;
	}

	if (inputX != 0 || inputY != 0) {
		gameStatus = NEW_TURN;
		if (player->moveOrAttack(player->x + inputX, player->y + inputY)) {
			map->computeFov();
		}
	}

	if (gameStatus == NEW_TURN) {
		for (Actor **iterator = actors.begin(); iterator != actors.end(); iterator++) {
			Actor *actor = *iterator;
			if (actor != player) {
				if (map->isInFov(actor->x, actor->y)) actor->update();
			}
		}
	}

	// Other combined/misc keypresses go here
	if (key.vk == TCODK_ENTER && key.lalt) TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
	if (key.vk == TCODK_ESCAPE) { if (TCODConsole::isFullscreen()) { TCODConsole::setFullscreen(false); } }
}

void Engine::render() {
	TCODConsole::root->clear();

	// Get console edges
	//conEdgeX = (TCODConsole::root->getWidth() - 1);
	//conEdgeY = (TCODConsole::root->getHeight() - 1);
	
	//Draw the map
	map->render();
	
	// Draw the actors
	for (Actor **iterator = actors.begin(); iterator != actors.end(); iterator++) {
		Actor *actor = *iterator;
		if (map->isInFov(actor->x, actor->y)) {
			actor->render();
		}
	}
}