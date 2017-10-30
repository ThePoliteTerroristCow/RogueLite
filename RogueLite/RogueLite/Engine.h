#pragma once

#define MAINCON_TITLE "libtcod C++ tutorial"
static const int FOV_RADIUS = 7; // Defines the FOV Radius. 0 for infinite.

class Engine {
public:
	TCODList<Actor *> actors; // List of all Actors on the map
	int fovRadius;
	Actor *player; // Pointer to the player actor
	Map *map;

	Engine();
	~Engine();
	void update();
	void render();

private:
	bool computeFov;

protected:
	int conEdgeX, conEdgeY;
};

extern Engine engine;