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
	TCODList<Actor *> actors; // List of all Actors on the map
	Actor *player; // Pointer to the player actor
	Map *map;
	FOV *fov;
	int screenWidth;
	int screenHeight;

	Engine(int screenWidth, int screenHeight);
	~Engine();
	void sendToBack(Actor *actor);
	void update();
	void render();

	int fovRadius;

private:
	int startupFov;

protected:
	int conEdgeX, conEdgeY;
};

extern Engine engine;