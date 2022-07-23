#pragma once
#include "Animal.h"

class Sheep :public Animal {
public:
	Sheep(World& w, int x, int y);
	void draw() override;
	std::string GetName() override;
	void Born(int x, int y) override;
};