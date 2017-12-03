static const int TRACKING_TURNS = 3;

class Ai {
public:
	// The =0 means that the method is a pure virtual method/abstract method. The Ai class has no 
	// implementation for this method. Thus, it is an abstract class that can't be instantiated.
	virtual void update(Actor *owner)=0;
};

class PlayerAi : public Ai {
public:
	void handleActionKey(Actor *owner, int ascii); // Handles single key-presses
	void handleActionKeys(); // Handles multi key-presses
	void update(Actor *owner);

protected:
	int inputX, inputY;
	bool moveOrAttack(Actor *owner, int targetX, int targetY);
};

class MonsterAi : public Ai {
public:
	void update(Actor *owner);

protected:
	int moveCount;
	void moveOrAttack(Actor *owner, int targetX, int targetY);
};