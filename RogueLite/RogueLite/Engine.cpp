#include <stdio.h>
#include "Main.h"

// CONSTRUCTOR 
Engine::Engine(int screenWidth, int screenHeight) : gameStatus(STARTUP), startupFov(fov.setFov(7)), screenWidth(screenWidth), screenHeight(screenHeight) {
	TCODConsole::initRoot(screenWidth, screenHeight, CON_MAIN_TITLE, false);
	player = new Actor(40, 25, '@', "player", TCODColor::white);
	player->destructible = new PlayerDestructible(30, 2, ""); 
	player->attacker = new Attacker(5); 
	player->ai = new PlayerAi(); 
	player->container = new Container(10); // player's default inventory space
	actors.push(player);
	map = new Map(80, 43);
	gui = new Gui();
	parser = new Parser();
	parser->setupConfigFiles();
	TCODConsole::setWindowTitle(engine.parser->cfgGraphics->cfg.values.cWindowTitle.c_str());
}

// DESTRUCTOR
Engine::~Engine() {
	actors.clearAndDelete();
	delete map;
	delete gui;
	delete parser;
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
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &lastKey, &mouse);
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
	
	//Draw the map
	if (cheats.sv.renderCheat == true) {
		map->renderCheat();
	} else map->render();
	
	// Draw the actors
	for (Actor **iterator = actors.begin(); iterator != actors.end(); iterator++) {
		Actor *actor = *iterator;
		if (map->isInFov(actor->x, actor->y)) {
			actor->render();
		}
	}

	// Render Player, stats, etc
	if (parser->cfgGraphics->cfg.values.iSetFramerate != 0) {
		if (parser->cfgGraphics->cfg.values.iSetFramerate < 0) parser->cfgGraphics->cfg.values.iSetFramerate = parser->cfgGraphics->cfg.defVals.iSetFramerate;
		TCODSystem::setFps(parser->cfgGraphics->cfg.values.iSetFramerate);
	}
	else TCODSystem::setFps(0);
	if (parser->cfgGraphics->cfg.values.iShowFramerate == 1) fFrameRate = TCODSystem::getFps();
	player->render();
	gui->render();
}