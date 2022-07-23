#include <iostream>
#include <windows.h> 
#include <vector>
#include "Guarana.h"
#include "World.h"

#define GUARANA_COLOR 12

using namespace std;

Guarana::Guarana(World& w, int x, int y)
	:Plant(w, 0, 0, x, y) {}

void Guarana::draw() {
	COORD c;
	c.X = x;
	c.Y = y + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, GUARANA_COLOR);
	cout << "G";
	world.SetTab(x, y, 'G');
}

string Guarana::GetName() {
	return "Guarana";
}

void Guarana::Born(int x, int y) {
	std::vector<Organism*>& organisms = world.Getorganisms();
	organisms.push_back(new Guarana(world, x, y));
	world.SetTab(x, y, 'G');
}