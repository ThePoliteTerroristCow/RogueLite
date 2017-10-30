#pragma once

static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 6;

static const int MIN_ROOM_MONSTERS = 0;
static const int MAX_ROOM_MONSTERS = 3;

struct Tile {
	bool explored; // has the player already seen this tile?
	Tile() : explored(false) {}
};

class Map {
public:
	int width, height;

	Map(int width, int height);
	~Map();
	void addMonster(int x, int y);
	bool canWalk(int x, int y) const;
	bool isWall(int x, int y) const;
	bool isInFov(int x, int y) const;
	bool isExplored(int x, int y) const;
	void computeFov();
	void render() const;
	void setWall(int x, int y);
	
protected:
	Tile *tiles;
	TCODMap *map;
	friend class BspListener;

	void dig(int x1, int y1, int x2, int y2);
	void createRoom(bool first, int x1, int y1, int x2, int y2);
};