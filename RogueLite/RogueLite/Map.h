//#pragma once

static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 6;
static const int MAX_ROOM_MONSTERS = 3;

struct Tile {
	bool explored; // has the player already seen this tile ?
	Tile() : explored(false) {}
};

class Map {
public:
	TCODMap *map;
	Tile *tiles;
	int width, height;

	Map(int width, int height);
	~Map();
	bool isWall(int x, int y) const;
	bool isInFov(int x, int y) const;
	bool isExplored(int x, int y) const;
	bool canWalk(int x, int y) const;
	void clearExplored(int x, int y);
	void computeFov();
	void render() const;
	void renderCheat() const;
	void generateNewDungeon(int x, int y);

protected:	
	friend class BspListener;

	void dig(int x1, int y1, int x2, int y2);
	void createRoom(bool first, int x1, int y1, int x2, int y2);
	void addMonster(int x, int y);
};