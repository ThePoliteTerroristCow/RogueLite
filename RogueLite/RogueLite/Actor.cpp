#include "stdafx.h"

Actor::Actor(int x, int y, int ch, const char *name, const TCODColor &col) :
	x(x), y(y), ch(ch), col(col) {
	strcpy_s(this->name, name);
}

void Actor::update() {
	//if (monsterType[0].compare(name) == 0) printf("The %s growls!\n", name);
	printf("The %s roars!\n", name);
}

void Actor::render() const {
	TCODConsole::root->setChar(x, y, ch);
	TCODConsole::root->setCharForeground(x, y, col);
}