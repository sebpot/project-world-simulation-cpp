#pragma once
#include "Organism.h"

#define BORNCHANCE 35

class Plant :public Organism {
public:
	Plant(World& w, int s, int i, int x, int y);
	void action() override;
	void collision(int m) override;
};