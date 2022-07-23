#pragma once
#include "Plant.h"

class Dandelion :public Plant {
public:
	Dandelion(World& w, int x, int y);
	void action() override;
	void draw() override;
	std::string GetName() override;
	void Born(int x, int y) override;
};