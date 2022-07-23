#include <iostream>
#include <windows.h> 
#include <vector>
#include "Fox.h"
#include "World.h"
#define FOX_COLOR 4

using namespace std;

Fox::Fox(World& w, int x, int y)
	:Animal(w, 3, 7, x, y) {}

bool Fox::isStronger() {
	if (world.GetTab(x, y) != '0') {
		std::vector<Organism*>& organisms = world.Getorganisms();
		for (Organism* o : organisms) {
			if (o->GetX() == this->x && o->GetY() == this->y && o->GetStrength() > this->strength) return false;
		}
	}
	return true;
}

void Fox::action() {
	int move, down=0, up=0, left=0, right=0;
	bool moved = false;
	while (moved == false) {
		if (down == 1 && up == 1 && left == 1 && right == 1) break;//jesli kazde pole jest zajete przez silniejszy organizm lis sie nie porusza
		move = rand() % 4;
		switch (move) {
		case UP:
			if (y > 1) {
				y--;
				if (isStronger() == false) {//sprawdzanie czy na polu nie stoi silniejszy organizm
					y++;
					up = 1;
				}
				else {
					moved = true;
					collision(UP);
				}
			}
			else up = 1;
			break;
		case DOWN:
			if (y < HEIGHT) {
				y++;
				if (isStronger() == false) {
					y--;
					down = 1;
				}
				else {
					moved = true;
					collision(DOWN);
				}
			}
			else down = 1;
			break;
		case LEFT:
			if (x > 1) {
				x--;
				if (isStronger() == false) {
					x++;
					left = 1;
				}
				else {
					moved = true;
					collision(LEFT);
				}
			}
			else left = 1;
			break;
		case RIGHT:
			if (x < WIDTH) {
				x++;
				if (isStronger() == false) {
					x--;
					right = 1;
				}
				else {
					moved = true;
					collision(RIGHT);
				}
			}
			else right = 1;
			break;
		}
	}
}

void Fox::draw() {
	COORD c;
	c.X = x;
	c.Y = y + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOX_COLOR);
	cout << "F";
	world.SetTab(x , y, 'F');
}

string Fox::GetName() {
	return "Fox";
}

void Fox::Born(int x, int y) {
	std::vector<Organism*>& organisms = world.Getorganisms();
	organisms.push_back(new Fox(world, x, y));
	world.SetTab(x, y, 'F');
}