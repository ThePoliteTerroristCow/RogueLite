class Lootable {
public:
	bool loot(Actor *owner, Actor *wearer);
	virtual bool use(Actor *owner, Actor *wearer);
};

class Healer : public Lootable {
public:
	float amount; // how much hp to heal

	Healer(float amount);
	bool use(Actor *owner, Actor *wearer);
};