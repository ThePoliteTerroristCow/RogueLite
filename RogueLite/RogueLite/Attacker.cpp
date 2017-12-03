#include <stdio.h>
#include "Main.h"

Attacker::Attacker(float power) : power(power) 
{}

void Attacker::attack(Actor *owner, Actor *target) {
	if (target->destructible && !target->destructible->isDead()) {
		if (power - target->destructible->defense > 0) {
			engine.gui->message(owner == engine.player ? TCODColor::red : TCODColor::lightGrey, true, "%s attacks %s for %d hit points.", owner->name, target->name, power - target->destructible->defense);
		}
		else { 
			engine.gui->message(TCODColor::lightGrey, true, "%s attacks %s but it has no effect!", owner->name, target->name);
		}
		target->destructible->takeDamage(target, power);
	}
	else {
		engine.gui->message(TCODColor::lightGrey, true, "%s attacks %s in vain.", owner->name, target->name);
	}
}