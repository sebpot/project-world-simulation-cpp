#pragma once
#include "Plant.h"

class Guarana :public Plant {
public:
	Guarana(World& w, int x, int y);
	void draw() override;
	std::string GetName() override;
	void Born(int x, int y) override;
};