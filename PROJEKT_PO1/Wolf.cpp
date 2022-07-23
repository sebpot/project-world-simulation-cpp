#include <iostream>
#include <windows.h> 
#include "Wolf.h"
#include "World.h"

#define WOLF_COLOR 8

using namespace std;

Wolf::Wolf(World& w, int x, int y)
	:Animal(w, 9, 5, x, y) {}

void Wolf::draw() {
	COORD c;
	c.X = x;
	c.Y = y + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, WOLF_COLOR);
	cout << "W";
	world.SetTab(x, y, 'W');
}

string Wolf::GetName() {
	return "Wolf";
}

void Wolf::Born(int x, int y) {
	std::vector<Organism*>& organisms = world.Getorganisms();
	organisms.push_back(new Wolf(world, x, y));
	world.SetTab(x, y, 'W');
}