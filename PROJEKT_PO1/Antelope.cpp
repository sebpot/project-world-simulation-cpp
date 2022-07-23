#include <iostream>
#include <windows.h> 
#include <vector>
#include "Antelope.h"
#include "World.h"

#define ANTELOPE_COLOR 6

using namespace std;

Antelope::Antelope(World& w, int x, int y)
	:Animal(w, 4, 4, x, y) {}

void Antelope::action() {
	int move;
	bool moved = false;
	while (moved == false) {
		move = rand() % 4;
		switch (move) {
		case UP:
			if (y > 2) {
				y -= 2;
				collision(UP);
				moved = true;
			}
			break;
		case DOWN:
			if (y < HEIGHT - 1) {
				y += 2;
				collision(DOWN);
				moved = true;
			}
			break;
		case LEFT:
			if (x > 2) {
				x -= 2;
				collision(LEFT);
				moved = true;
			}
			break;
		case RIGHT:
			if (x < WIDTH - 1) {
				x += 2;
				collision(RIGHT);
				moved = true;
			}
			break;
		}
	}
}

void Antelope::draw() {
	COORD c;
	c.X = x;
	c.Y = y + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, ANTELOPE_COLOR);
	cout << "A";
	world.SetTab(x, y, 'A');
}

string Antelope::GetName() {
	return "Antelope"; 
}

void Antelope::Born(int x, int y) {
	std::vector<Organism*>& organisms = world.Getorganisms();
	organisms.push_back(new Antelope(world, x, y));
	world.SetTab(x, y, 'A');
}

bool Antelope::flee(Organism& attacker) {
	int runaway, move;
	bool moved = false;
	runaway = rand() % 2;
	if (runaway == 0 && (world.GetTab(x, y - 1) == '0' || world.GetTab(x, y + 1) == '0' || world.GetTab(x - 1, y) == '0' || world.GetTab(x + 1, y) == '0')) {//jest 50% szans na ucieczke i sprawdzamy czy jest miejsce gdzie antylopa moze uciec
		world.AddEvent(attacker.GetName() + " attacks " + this->GetName() + ", but it flees from the fight.");
		while (moved == false) {
			move = rand() % 4;
			switch (move) {
			case UP:
				if (world.GetTab(x, y - 1) == '0') {
					y--;
					world.SetTab(x, y, 'A');
					moved = true;
				}
				break;
			case DOWN:
				if (world.GetTab(x, y + 1) == '0') {
					y++;
					world.SetTab(x, y, 'A');
					moved = true;
				}
				break;
			case LEFT:
				if (world.GetTab(x - 1, y) == '0') {
					x--;
					world.SetTab(x, y, 'A');
					moved = true;
				}
				break;
			case RIGHT:
				if (world.GetTab(x + 1, y) == '0') {
					x++;
					world.SetTab(x, y, 'A');
					moved = true;
				}
				break;
			}
		}
		return true;
	}
	else return false;
}