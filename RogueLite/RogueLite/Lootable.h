class Lootable {
public:
	bool loot(Actor *owner, Actor *wearer);
	virtual bool use(Actor *owner, Actor *wearer);
};

class Healer : public Lootable {
public:
	float amount; // how much of something to do (ie. heal hp, add to DEF, etc)

	Healer(float amount);
	bool use(Actor *owner, Actor *wearer);
};