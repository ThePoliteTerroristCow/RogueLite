#include "stdafx.h"

class BspListener : public ITCODBspCallback {
private:
	Map &map; // a map to dig
	int roomNum; // number of rooms
	int lastx, lasty; // center of last room
public:
	BspListener(Map &map) : map(map), roomNum(0) {}
	bool visitNode(TCODBsp *node, void *userData) {
		if (node->isLeaf()) {
			int x, y, w, h;
			// dig a room
			TCODRandom *rng = TCODRandom::getInstance();
			w = rng->getInt(ROOM_MIN_SIZE, node->w - 2);
			h = rng->getInt(ROOM_MIN_SIZE, node->h - 2);
			x = rng->getInt(node->x + 1, node->x + node->w - w - 1);
			y = rng->getInt(node->y + 1, node->y + node->h - h - 1);
			map.createRoom(roomNum == 0, x, y, x + w - 1, y + h - 1);
			
			if (roomNum != 0) {
				// dig a corridor from the last room
				map.dig(lastx, lasty, x + w / 2, lasty);
				map.dig(x + 2 / 2, lasty, x + 2 / 2, y + h / 2);
			}
			lastx = x + 2 / 2;
			lasty = y + h / 2;
			roomNum++;
		}
		return true;
	}
};

Map::Map(int width, int height) : width(width), height(height) {
	tiles = new Tile[width*height];
	map = new TCODMap(width, height);
	TCODBsp bsp(0, 0, width, height);
	bsp.splitRecursive(NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
	BspListener listener(*this);
	bsp.traverseInvertedLevelOrder(&listener, NULL);
}

Map::~Map() {
	delete[] tiles; // Releases everything that was allocated in the constructor
	delete map;
}

//////////////////////////////////////////////////////////////////////////
// MONSTER SPAWNING & HANDLING
void Map::addMonster(int x, int y) {
	TCODRandom *rng = TCODRandom::getInstance();
	if (rng->getInt(0, 100) < 80) { // creates an orc in 80% of cases
		// create an orc
		engine.actors.push(new Actor(x, y, 'o', "orc", TCODColor::desaturatedGreen));
	}
	else {
		// create a troll
		engine.actors.push(new Actor(x, y, 'T', "troll", TCODColor::darkerGreen));
	}
}

//////////////////////////////////////////////////////////////////////////
// GENERAL MAP FUNCTIONS

bool Map::canWalk(int x, int y) const { 
	if (isWall(x, y)) {
		return false; // this is a wall
	}
	for (Actor **iterator = engine.actors.begin(); iterator != engine.actors.end(); iterator++) {
		Actor *actor = *iterator;
		if (actor->x == x && actor->y == y) {
			return false; // there is an actor here. cannot walk
		}
	}
	return true;
}

bool Map::isWall(int x, int y) const {
	//return !tiles[x + y*width].canWalk;
	return !map->isWalkable(x, y);
}

void Map::setWall(int x, int y) {
	map->setProperties(x, y, false, false);
	//tiles[x + y*width].canWalk = false;
}

//////////////////////////////////////////////////////////////////////////
// FOV FUNCTIONS

bool Map::isExplored(int x, int y) const {
	return tiles[x + y*width].explored;
}

bool Map::isInFov(int x, int y) const {
	if (map->isInFov(x, y)) {
		tiles[x + y*width].explored = true;
		return true;
	}
	return false;
}

void Map::computeFov() {
	map->computeFov(engine.player->x, engine.player->y, engine.fovRadius);
}

//////////////////////////////////////////////////////////////////////////
// BSP DUNGEON CREATION FUNCTIONS

void Map::dig(int x1, int y1, int x2, int y2) {
	if (x2 < x1) {
		int tmp = x2;
		x2 = x1;
		x1 = tmp;
	}
	if (y2 < y1) {
		int tmp = y2;
		y2 = y1;
		y1 = tmp;
	}
	for (int tileX = x1; tileX <= x2; tileX++) {
		for (int tileY = y1; tileY <= y2; tileY++) {
			map->setProperties(tileX, tileY, true, true);
		}
	}
}

void Map::createRoom(bool first, int x1, int y1, int x2, int y2) {
	dig(x1, y1, x2, y2);
	if (first) {
		// Puts the player in the first room generated
		engine.player->x = (x1 + x2) / 2;
		engine.player->y = (y1 + y2) / 2;
		// Include a block type here to act as a rope/ladder/staircase/tunnel/door/etc. 
		// It should spawn next to the player in the first immediately open cardinal direction
	}
	else {
		TCODRandom *rng = TCODRandom::getInstance();
		int nbMonsters = rng->getInt(MIN_ROOM_MONSTERS, MAX_ROOM_MONSTERS);
		while (nbMonsters > 0) {
			int x = rng->getInt(x1, x2); // get random 'x' position inside the room
			int y = rng->getInt(y1, y2); // get random 'y' position inside the room
			if (canWalk(x, y)) {
				addMonster(x, y);
			}
			nbMonsters--;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// MAP RENDERING

// Scans the whole map and fills the console background color with the right colors
void Map::render() const {
	static const TCODColor darkWall(0, 0, 100);
	static const TCODColor darkGround(50, 50, 150);
	static const TCODColor lightWall(130, 110, 50);
	static const TCODColor lightGround(200, 180, 50);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (isInFov(x, y)) {
				TCODConsole::root->setCharBackground(x, y, isWall(x, y) ? lightWall : lightGround);
			}
			else if (isExplored(x, y)) {
				TCODConsole::root->setCharBackground(x, y, isWall(x, y) ? darkWall : darkGround);
			}
		}
	}
}