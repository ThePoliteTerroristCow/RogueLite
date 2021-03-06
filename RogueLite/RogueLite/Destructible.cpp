#include <stdio.h>
#include "Main.h"

Destructible::Destructible(float maxHp, float defense, const char *corpseName) : maxHp(maxHp), currentHp(maxHp), defense(defense), corpseName(corpseName) {
}

float Destructible::takeDamage(Actor *owner, float damage) {
	damage -= defense;
	if (damage > 0) {
		currentHp -= damage;
		if (currentHp <= 0) {
			die(owner);
		}
	}
	else {
		damage = 0;
	}
	return damage;
}

void Destructible::die(Actor *owner) {
	// Transform the actor into a corpse
	owner->ch = '%';
	owner->col = TCODColor::darkRed;
	owner->name = corpseName;
	owner->blocks = false;
	// make sure corpses are drawn before living actors
	engine.sendToBack(owner);
}

//////////////////////////////////////////////////////////////////////////

MonsterDestructible::MonsterDestructible(float maxHp, float defense, const char *corpseName) : Destructible(maxHp, defense, corpseName) 
{}

void MonsterDestructible::die(Actor *owner) {
	printf("%s is dead\n", owner->name);
	Destructible::die(owner);
}

PlayerDestructible::PlayerDestructible(float maxHp, float defense, const char *corpseName) : Destructible(maxHp, defense, corpseName) 
{}

void PlayerDestructible::die(Actor *owner) {
	printf("You died!\n");
	Destructible::die(owner);
	engine.gameStatus = Engine::DEFEAT;
}