#pragma once
#include "Plant.h"

class Grass :public Plant {
public:
	Grass(World& w, int x, int y);
	void draw() override;
	std::string GetName() override;
	void Born(int x, int y) override;
};