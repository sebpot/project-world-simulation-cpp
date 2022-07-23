#include <iostream>
#include "Plant.h"
#include "World.h"

Plant::Plant(World& w, int s, int i, int x, int y)
	:Organism(w, s, i, x, y) {}

void Plant::action() {
	int bornchance, where;
	bool borned = false;
	bornchance = rand() % BORNCHANCE;
	if (bornchance == 0 && (world.GetTab(x, y - 1) == '0' || world.GetTab(x, y + 1) == '0' || world.GetTab(x - 1, y) == '0' || world.GetTab(x + 1, y) == '0')) {//sprawdzanie czy jest miejsce na nowy organizm
		world.AddEvent("A new " + this->GetName() + " grows.");
		while (borned == false) {
			where = rand() % 4;
			switch (where) {
			case UP:
				if (y > 1 && world.GetTab(x, y - 1) == '0') {
					Born(x, y - 1);
					borned = true;
				}
				break;
			case DOWN:
				if (y < HEIGHT && world.GetTab(x, y + 1) == '0') {
					Born(x, y + 1);
					borned = true;
				}
				break;
			case LEFT:
				if (x > 1 && world.GetTab(x - 1, y) == '0') {
					Born(x - 1, y);
					borned = true;
				}
				break;
			case RIGHT:
				if (x < WIDTH && world.GetTab(x + 1, y) == '0') {
					Born(x + 1, y);
					borned = true;
				}
				break;
			}
		}
	}
}

void Plant::collision(int m) {}
