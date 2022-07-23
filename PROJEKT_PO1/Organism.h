#pragma once
class World;

class Organism {
protected:
	int strength, initiative, x, y;
	World& world;
public:
	Organism(World& w, int s, int i, int x, int y);
	virtual void action()=0;
	virtual void collision(int m)=0;
	virtual void draw()=0;
	virtual void setmove(int m);
	int GetX();
	int GetY();
	int GetStrength();
	int GetInitiative();
	virtual std::string GetName()=0;
	virtual void Born(int x, int y)=0;
	void SetX(int x_new);
	void SetY(int y_new);
	void SetStrength(int s);
	virtual bool defend(Organism& attacker);
	virtual bool flee(Organism& attacker);
	virtual bool shield(Organism& attacker, int m);
	virtual int GetSpecial();
	virtual void SetSpecial(int s);
};
