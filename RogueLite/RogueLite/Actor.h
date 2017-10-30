#pragma once

#define MAX_NAME_SIZE 40

class Actor {
public:
	int x;
	int y;
	int ch;
	TCODColor col;

	char name[MAX_NAME_SIZE];

	Actor(int x, int y, int ch, const char *name, const TCODColor &col);
	bool moveOrAttack(int x, int y);
	void update();

	void render() const;
};