#include "stdafx.h"

// CONSTRUCTOR 
Engine::Engine() : fovRadius(FOV_RADIUS), computeFov(true) {
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

// Handles the player walking code & associated collision detection
void Engine::update() {
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
	switch (key.vk) {
	
	case TCODK_UP:
		if (player->y <= 0) { player->y++; }
		if (map->isWall(player->x, player->y - 1) == false) { player->y--; computeFov = true; } break;

	case TCODK_DOWN:
		if (player->y >= conEdgeY) { player->y--; }
		if (map->isWall(player->x, player->y + 1) == false) { player->y++; computeFov = true; } break;

	case TCODK_LEFT:
		if (player->x <= 0) { player->x++; }
		if (map->isWall(player->x - 1, player->y) == false) { player->x--; computeFov = true; } break;

	case TCODK_RIGHT:
		if (player->x >= conEdgeX) { player->x--; }
		if (map->isWall(player->x + 1, player->y) == false) { player->x++; computeFov = true; } break;

	default: 
		break;
	}
	if (computeFov) {
		map->computeFov();
		computeFov = false;
	}

	// Other combined/misc keypresses go here
	if (key.vk == TCODK_ENTER && key.lalt) TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
}

void Engine::render() {
	TCODConsole::root->clear();

	// Get console edges
	conEdgeX = (TCODConsole::root->getWidth() - 1);
	conEdgeY = (TCODConsole::root->getHeight() - 1);
	
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