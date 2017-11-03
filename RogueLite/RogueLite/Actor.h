//#pragma once

class Actor {
public:
	int x;
	int y;
	int ch;
	TCODColor col;
	const char *name;

	bool blocks; // can we walk on this actor?
	Attacker *attacker; // something that deal damage
	Destructible *destructible; // something that can be damaged
	Ai *ai; // something self-updating

	Actor(int x, int y, int ch, const char *name, const TCODColor &col);
	void update(); // Calls 'ai->update(Actor *owner)'
	void render() const;
};