#pragma once
#include "Animal.h"

class Fox :public Animal {
public:
	Fox(World& w, int x, int y);
	void action() override;
	void draw() override;
	bool isStronger();
	std::string GetName() override;
	void Born(int x, int y) override;
};