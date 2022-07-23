#pragma once
#include "Animal.h"

class Antelope :public Animal {
public:
	Antelope(World& w, int x, int y);
	void action() override;
	void draw() override;
	std::string GetName() override;
	void Born(int x, int y) override;
	bool flee(Organism& attacker) override;
};