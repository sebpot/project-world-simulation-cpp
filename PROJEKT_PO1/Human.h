#pragma once
#include "Animal.h"

class Human :public Animal {
private:
	int move;
	int special;
public:
	Human(World& w, int x, int y, int s);
	void action() override;
	void draw() override;
	void setmove(int m) override;
	std::string GetName() override;
	void Born(int x, int y) override;
	bool shield(Organism& attacker, int m) override;
	int GetSpecial() override;
	void SetSpecial(int s) override;
};