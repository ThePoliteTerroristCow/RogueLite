#include "Main.h"

// CONSTRUCTOR 
Engine::Engine(int screenWidth, int screenHeight) : gameStatus(STARTUP), currentFov(fov->setFov(7)), screenWidth(screenWidth), screenHeight(screenHeight) {
	TCODConsole::initRoot(screenWidth, screenHeight, CON_MAIN_TITLE, false);
	player = new Actor(40, 25, '@', "player", TCODColor::white);
	player->destructible = new PlayerDestructible(30, 2, "your carcass");
	player->attacker = new Attacker(5);
	player->ai = new PlayerAi();
	actors.push(player);
}

// DESTRUCTOR
Engine::~Engine() {
	actors.clearAndDelete();
	delete map;
}

//////////////////////////////////////////////////////////////////////////

void Engine::sendToBack(Actor *actor) {
	actors.remove(actor);
	actors.insertBefore(actor, 0);
}

// Checks the player actor and then iterates through & updates all the other actors in the scene
void Engine::update() {
	if (gameStatus == STARTUP) map->computeFov();
	gameStatus = IDLE;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, NULL);
	player->update();

	if (gameStatus == NEW_TURN) {
		for (Actor **iterator = actors.begin(); iterator != actors.end(); iterator++) {
			Actor *actor = *iterator;
			if (actor != player) {
				actor->update();
			}
		}
	}
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

	// Render Player, stats, etc
	player->render();
	TCODConsole::root->print(1, screenHeight - 2, "HP: %d/%d", (int)player->destructible->currentHp, (int)player->destructible->maxHp);
}