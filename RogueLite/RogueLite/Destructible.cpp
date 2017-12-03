#include <stdio.h>
#include "Main.h"

Destructible::Destructible(float maxHp, float defense, const char *corpseName) : maxHp(maxHp), currentHp(maxHp), defense(defense), corpseName(corpseName) {
}

float Destructible::heal(float amount) {
	currentHp += amount;
	if (currentHp > maxHp) {
		amount -= currentHp - maxHp;
		currentHp = maxHp;
	}
	return amount;
}

float Destructible::takeDamage(Actor *owner, float damage) {
	// Circumvent damage if Godmode is active
	if (cheats.sv.bGodmode == true) {
		if (owner == engine.player) {
			cheats.setMaxHealth(engine.player);
			return damage - damage;
		}
	}

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
	engine.gui->message(TCODColor::lightGrey, true, "%s is dead", owner->name);
	Destructible::die(owner);
}

PlayerDestructible::PlayerDestructible(float maxHp, float defense, const char *corpseName) : Destructible(maxHp, defense, corpseName) 
{}

void PlayerDestructible::die(Actor *owner) {
	// Circumvent death if Godmode is active
	if (cheats.sv.bGodmode == true) {
		engine.player->destructible->currentHp = engine.player->destructible->maxHp;
		return;
	}

	engine.gui->message(TCODColor::red, "You died!", false);
	Destructible::die(owner);
	engine.gameStatus = Engine::DEFEAT;
}