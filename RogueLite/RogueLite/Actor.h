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
	Lootable *lootable; // something that can be picked and used
	Container *container; // something that can contain actors

	Actor(int x, int y, int ch, const char *name, const TCODColor &col);
	~Actor();
	void update(); // Calls 'ai->update(Actor *owner)'
	void render() const;
};