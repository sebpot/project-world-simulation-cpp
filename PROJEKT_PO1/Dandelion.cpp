#include <iostream>
#include <windows.h> 
#include <vector>
#include "Dandelion.h"
#include "World.h"

#define DANDELION_COLOR 14

using namespace std;

Dandelion::Dandelion(World& w, int x, int y)
	:Plant(w, 0, 0, x, y) {}

void Dandelion::action() {
	int bornchance, where;
	bool borned = false;
	for (int i = 0; i < 3; i++) {//3 podejscia dla mleczy
		if (borned == true) break;
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
}

void Dandelion::draw() {
	COORD c;
	c.X = x;
	c.Y = y + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, DANDELION_COLOR);
	cout << "d";
	world.SetTab(x, y, 'd');
}

string Dandelion::GetName() {
	return "dandelion";
}

void Dandelion::Born(int x, int y) {
	std::vector<Organism*>& organisms = world.Getorganisms();
	organisms.push_back(new Dandelion(world, x, y));
	world.SetTab(x, y, 'd');
}