#pragma once
#include "Plant.h"

class Belladonna :public Plant {
public:
	Belladonna(World& w, int x, int y);
	void draw() override;
	std::string GetName() override;
	void Born(int x, int y) override;
};