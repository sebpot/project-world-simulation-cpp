#pragma once
#include "Organism.h"

class Animal :public Organism {
public:
	Animal(World& w, int s, int i, int x, int y);
	void action() override;
	void collision(int m) override;
	void breeding();
};
