#include <iostream>
#include <windows.h> 
#include <vector>
#include "Turtle.h"
#include "World.h"

#define TURTLE_COLOR 2

using namespace std;

Turtle::Turtle(World& w, int x, int y)
	:Animal(w, 2, 1, x, y) {}

void Turtle::action() {
	int move, ismoving;
	bool moved = false;
	ismoving = rand() % 4;//tylko 25% szansy na ruch zolkia
	if (ismoving == 0) {
		while (moved == false) {
			move = rand() % 4;
			switch (move) {
			case UP:
				if (y > 1) {
					y--;
					collision(UP);
					moved = true;
				}
				break;
			case DOWN:
				if (y < HEIGHT) {
					y++;
					collision(DOWN);
					moved = true;
				}
				break;
			case LEFT:
				if (x > 1) {
					x--;
					collision(LEFT);
					moved = true;
				}
				break;
			case RIGHT:
				if (x < WIDTH) {
					x++;
					collision(RIGHT);
					moved = true;
				}
				break;
			}
		}
	}
}

void Turtle::draw() {
	COORD c;
	c.X = x;
	c.Y = y + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, TURTLE_COLOR);
	cout << "T";
	world.SetTab(x, y, 'T');
}

string Turtle::GetName() {
	return "Turtle";
}

void Turtle::Born(int x, int y) {
	std::vector<Organism*>& organisms = world.Getorganisms();
	organisms.push_back(new Turtle(world, x, y));
	world.SetTab(x, y, 'T');
}

bool Turtle::defend(Organism& attacker) {
	if (attacker.GetStrength() < 5) {
		world.AddEvent(attacker.GetName() + " attacks " + this->GetName() + " , but his shell is too hard.");
		return true;
	}
	else return false;
}