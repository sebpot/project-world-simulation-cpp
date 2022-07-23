#pragma once
#include "Animal.h"

class Wolf :public Animal {
public:
	Wolf(World& w, int x, int y);
	void draw() override;
	std::string GetName() override;
	void Born(int x, int y) override;
};