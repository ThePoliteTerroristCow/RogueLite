#include "Main.h"

bool Lootable::loot(Actor *owner, Actor *wearer) {
	if (wearer->container && wearer->container->add(owner)) {
		engine.actors.remove(owner);
		return true;
	}
	return false;
}

bool Lootable::use(Actor *owner, Actor *wearer) {
	if (wearer->container) {
		wearer->container->remove(owner);
		delete owner;
		return true;
	}
	return false;
}

Healer::Healer(float amount) : amount(amount) {}
bool Healer::use(Actor *owner, Actor *wearer) {
	if (wearer->destructible) {
		float amountHealed = wearer->destructible->heal(amount);
		if (amountHealed > 0) {
			return Lootable::use(owner, wearer);
		}
	}
	return false;
}