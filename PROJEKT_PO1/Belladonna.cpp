#include <iostream>
#include <windows.h> 
#include <vector>
#include "Belladonna.h"
#include "World.h"

#define BELLADONNA_COLOR 13

using namespace std;

Belladonna::Belladonna(World& w, int x, int y)
	:Plant(w, 99, 0, x, y) {}

void Belladonna::draw() {
	COORD c;
	c.X = x;
	c.Y = y + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BELLADONNA_COLOR);
	cout << "b";
	world.SetTab(x, y, 'b');
}

string Belladonna::GetName() {
	return "belladonna (deadly nightshade)";
}

void Belladonna::Born(int x, int y) {
	std::vector<Organism*>& organisms = world.Getorganisms();
	organisms.push_back(new Belladonna(world, x, y));
	world.SetTab(x, y, 'b');
}