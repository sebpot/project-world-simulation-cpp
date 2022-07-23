#pragma once
#include "Plant.h"

class Sosnowskys_hogweed :public Plant {
public:
	Sosnowskys_hogweed(World& w, int x, int y);
	void action() override;
	void draw() override;
	std::string GetName() override;
	void Born(int x, int y) override;
};