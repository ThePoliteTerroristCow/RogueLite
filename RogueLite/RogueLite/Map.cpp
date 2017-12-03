#include <stdio.h>
#include "Main.h"

class BspListener : public ITCODBspCallback {
private:
	Map &map; // a map to dig
	int roomNum; // room number
	int lastx, lasty; // center of the last room
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
				// dig a corridor from last room
				map.dig(lastx, lasty, x + w / 2, lasty);
				map.dig(x + w / 2, lasty, x + w / 2, y + h / 2);
			}
			lastx = x + w / 2;
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
	delete[] tiles;
	delete map;
}

//////////////////////////////////////////////////////////////////////////
// Room Creation & Regenerating Dungeons

void Map::createRoom(bool first, int x1, int y1, int x2, int y2) {
	dig(x1, y1, x2, y2);
	if (first) {
		// put the player in the first room
		engine.player->x = (x1 + x2) / 2;
		engine.player->y = (y1 + y2) / 2;
	}
	else {
		TCODRandom *rng = TCODRandom::getInstance();
		int nbMonsters = rng->getInt(0, MAX_ROOM_MONSTERS);
		while (nbMonsters > 0) {
			int x = rng->getInt(x1, x2);
			int y = rng->getInt(y1, y2);
			if (canWalk(x, y)) {
				addMonster(x, y);
			}
			nbMonsters--;
		}
	}
}

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
	for (int tilex = x1; tilex <= x2; tilex++) {
		for (int tiley = y1; tiley <= y2; tiley++) {
			map->setProperties(tilex, tiley, true, true);
		}
	}
}

void Map::generateNewDungeon(int x, int y) {
	engine.map->~Map();
	tiles = new Tile[x * y];
	map = new TCODMap(x, y);
	TCODBsp bsp(0, 0, x, y);
	TCODRandom *rng = TCODRandom::getInstance();
	bsp.splitRecursive(rng, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
	BspListener listener(*this);
	bsp.traverseInvertedLevelOrder(&listener, NULL);
	
	if (!isWall(engine.player->x + 1, engine.player->y)) {
		addItem(engine.player->x + 1, engine.player->y);
	}
	else if (!isWall(engine.player->x - 1, engine.player->y)) {
		addItem(engine.player->x - 1, engine.player->y);
	}
}

//////////////////////////////////////////////////////////////////////////
// Adding Monsters

void Map::addMonster(int x, int y) {
	TCODRandom *rng = TCODRandom::getInstance();
	if (rng->getInt(0, 100) < 80) {
		// create an orc
		Actor *orc = new Actor(x, y, 'o', "Orc", TCODColor::desaturatedGreen);
		orc->destructible = new MonsterDestructible(10, 0, "Dead orc");
		orc->attacker = new Attacker(3);
		orc->ai = new MonsterAi();
		engine.actors.push(orc);
	}
	else {
		// create a troll
		Actor *troll = new Actor(x, y, 'T', "Troll", TCODColor::darkerGreen);
		troll->destructible = new MonsterDestructible(16, 1, "Troll carcass");
		troll->attacker = new Attacker(4);
		troll->ai = new MonsterAi();
		engine.actors.push(troll);
	}
}

//////////////////////////////////////////////////////////////////////////
// Map & Fov Properties

bool Map::isWall(int x, int y) const {
	return !map->isWalkable(x, y);
}

bool Map::canWalk(int x, int y) const {
	if (isWall(x, y)) {
		// this is a wall
		return false;
	}
	for (Actor **iterator = engine.actors.begin();
		iterator != engine.actors.end(); iterator++) {
		Actor *actor = *iterator;
		if (actor->blocks && actor->x == x && actor->y == y) {
			// there is a blocking actor here. cannot walk
			return false;
		}
	}
	return true;
}

bool Map::isExplored(int x, int y) const {
	return tiles[x + y*width].explored;
}

bool Map::isInFov(int x, int y) const {
	if (x < 0 || x >= width || y < 0 || y >= height) {
		return false;
	}
	if (map->isInFov(x, y)) {
		tiles[x + y*width].explored = true;
		return true;
	}
	return false;
}

void Map::clearExplored(int x, int y) {
	for (int i = 0; i < x; i++) {
		for (int i = 0; i < y; i++) {
			if (isExplored(x, y) == true) {
				tiles[x + y*width].explored = false;
			}
		}
	}
}

void Map::computeFov() {
	map->computeFov(engine.player->x, engine.player->y, fov.currentFov);
}

//////////////////////////////////////////////////////////////////////////
// Map Rendering

void Map::renderCheat() const {
	static const TCODColor lightWall(130, 110, 50);
	static const TCODColor lightGround(200, 180, 50);

	/* array shenanigans
			int *canWalkX = NULL, *canWalkY = NULL;
			int xSize = width;
			int ySize = height;
			canWalkX = new int[xSize];
			canWalkY = new int[ySize];
			for (int i = 0; i < xSize; i++) { canWalkX[i] = 0; }
			for (int i = 0; i < ySize; i++) { canWalkY[i] = 0; }

			// cleanup the array when done
			delete[] canWalkX;
			delete[] canWalkY;
			canWalkX = NULL;
			canWalkY = NULL;
	*/
	if (cheats.sv.renderCheat == true) {
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				if (canWalk(x, y))
				{
					TCODConsole::root->setCharBackground(x, y, lightGround);
				}
				else if (isWall(x, y))
				{
					TCODConsole::root->setCharBackground(x, y, lightWall);
				}
			}
		}
	}
	for (Actor **iterator = engine.actors.begin(); iterator != engine.actors.end(); iterator++) {
		Actor *actor = *iterator;
		if (cheats.sv.renderCheat == true)
		{
			map->setInFov(actor->x, actor->y, true);
		}
		else {
			map->setInFov(actor->x, actor->y, false);
			engine.map->clearExplored(actor->x, actor->y);
		}
	}
}

void Map::render() const {
	static const TCODColor darkWall(0, 0, 100);
	static const TCODColor darkGround(50, 50, 150);
	static const TCODColor lightWall(130, 110, 50);
	static const TCODColor lightGround(200, 180, 50);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (isInFov(x, y)) {
				TCODConsole::root->setCharBackground(x, y,
					isWall(x, y) ? lightWall : lightGround);
			}
			else if (isExplored(x, y)) {
				TCODConsole::root->setCharBackground(x, y,
					isWall(x, y) ? darkWall : darkGround);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void Map::addItem(int x, int y) {
	Actor *healthPotion = new Actor(x, y, '!', "Health Potion", TCODColor::violet);
	healthPotion->blocks = false;
	healthPotion->lootable = new Lootable();
	engine.actors.push(healthPotion);
}