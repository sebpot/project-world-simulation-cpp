#include <iostream>
#include <windows.h> 
#include <vector>
#include "Grass.h"
#include "World.h"

#define GRASS_COLOR 10

using namespace std;

Grass::Grass(World& w, int x, int y)
	:Plant(w, 0, 0, x, y) {}

void Grass::draw() {
	COORD c;
	c.X = x;
	c.Y = y + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, GRASS_COLOR);
	cout << "g";
	world.SetTab(x, y, 'g');
}

string Grass::GetName() {
	return "grass";
}

void Grass::Born(int x, int y) {
	std::vector<Organism*>& organisms = world.Getorganisms();
	organisms.push_back(new Grass(world, x, y));
	world.SetTab(x, y, 'g');
}