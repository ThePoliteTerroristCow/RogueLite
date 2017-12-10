//#pragma once

#define CON_MAIN_TITLE "libtcod C++ tutorial"

class Engine {
public:
	enum GameStatus {
		STARTUP,
		IDLE,
		NEW_TURN,
		VICTORY,
		DEFEAT
	} gameStatus;

	TCOD_key_t lastKey;
	TCOD_mouse_t mouse;
	TCODList<Actor *> actors; // List of all Actors on the map
	Actor *player; // Pointer to the player actor
	Gui *gui;
	Map *map;
	Parser *parser;

	float fFrameRate;
	int screenWidth;
	int screenHeight;

	Engine(int screenWidth, int screenHeight);
	~Engine();
	void sendToBack(Actor *actor);
	void update();
	void render();

private:
	int startupFov;
};

extern Engine engine;