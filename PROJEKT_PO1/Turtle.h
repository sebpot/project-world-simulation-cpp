#pragma once
#include "Animal.h"

class Turtle :public Animal {
public:
	Turtle(World& w, int x, int y);
	void action() override;
	void draw() override;
	std::string GetName() override;
	void Born(int x, int y) override;
	bool defend(Organism& attacker) override;
};