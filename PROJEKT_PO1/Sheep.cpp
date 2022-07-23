#include <iostream>
#include <windows.h> 
#include "Sheep.h"
#include "World.h"

#define HUMAN_COLOR 15

using namespace std;

Sheep::Sheep(World& w, int x, int y)
	:Animal(w, 4, 4, x, y) {}

void Sheep::draw() {
	COORD c;
	c.X = x;
	c.Y = y + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, HUMAN_COLOR);
	cout << "S";
	world.SetTab(x, y, 'S');
}

string Sheep::GetName() {
	return "Sheep";
}

void Sheep::Born(int x, int y) {
	std::vector<Organism*>& organisms = world.Getorganisms();
	organisms.push_back(new Sheep(world, x, y));
	world.SetTab(x, y, 'S');
}