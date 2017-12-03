#include "Main.h"

Container::Container(int size) : size(size) {}

Container::~Container() {
	inventory.clearAndDelete();
}

bool Container::add(Actor *actor) {
	if (size > 0 && inventory.size() >= size) {
		// inventory full
		return false;
	}
}

void Container::remove(Actor *actor) {
	inventory.remove(actor);
}