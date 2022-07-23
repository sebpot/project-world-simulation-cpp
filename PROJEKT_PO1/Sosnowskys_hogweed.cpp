#include <iostream>
#include <windows.h> 
#include <vector>
#include "Sosnowskys_hogweed.h"
#include "World.h"

#define SOS_HOG_COLOR 3

using namespace std;

Sosnowskys_hogweed::Sosnowskys_hogweed(World& w, int x, int y)
	:Plant(w, 10, 0, x, y) {}

void Sosnowskys_hogweed::action() {
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
	//barszcz sprawdza wszystkie pola dookola eliminujac wszystkie organizmy jakie znajdzie
	std::vector<Organism*>& organisms = world.Getorganisms();
	if (world.GetTab(x, y - 1) == 'A' || world.GetTab(x, y - 1) == 'F' || world.GetTab(x, y - 1) == 'H' || world.GetTab(x, y - 1) == 'S' || world.GetTab(x, y - 1) == 'T' || world.GetTab(x, y - 1) == 'W') {
		for (Organism* o : organisms) {
			if (o->GetX() == x && o->GetY() == y - 1) {
				o->SetX(0);
				o->SetY(0);
				world.SetTab(x, y - 1, '0');
				world.AddEvent(this->GetName() + " kills " + o->GetName() + ".");
				break;
			}
		}
	}

	if (world.GetTab(x, y + 1) == 'A' || world.GetTab(x, y + 1) == 'F' || world.GetTab(x, y + 1) == 'H' || world.GetTab(x, y + 1) == 'S' || world.GetTab(x, y + 1) == 'T' || world.GetTab(x, y + 1) == 'W') {
		for (Organism* o : organisms) {
			if (o->GetX() == x && o->GetY() == y + 1) {
				o->SetX(0);
				o->SetY(0);
				world.SetTab(x, y + 1, '0');
				world.AddEvent(this->GetName() + " kills " + o->GetName() + ".");
				break;
			}
		}
	}

	if (world.GetTab(x - 1, y) == 'A' || world.GetTab(x - 1, y) == 'F' || world.GetTab(x - 1, y) == 'H' || world.GetTab(x - 1, y) == 'S' || world.GetTab(x - 1, y) == 'T' || world.GetTab(x - 1, y) == 'W') {
		for (Organism* o : organisms) {
			if (o->GetX() == x - 1 && o->GetY() == y) {
				o->SetX(0);
				o->SetY(0);
				world.SetTab(x - 1, y, '0');
				world.AddEvent(this->GetName() + " kills " + o->GetName() + ".");
				break;
			}
		}
	}

	if (world.GetTab(x + 1, y) == 'A' || world.GetTab(x + 1, y) == 'F' || world.GetTab(x + 1, y) == 'H' || world.GetTab(x + 1, y) == 'S' || world.GetTab(x + 1, y) == 'T' || world.GetTab(x + 1, y) == 'W') {
		for (Organism* o : organisms) {
			if (o->GetX() == x + 1 && o->GetY() == y) {
				o->SetX(0);
				o->SetY(0);
				world.SetTab(x + 1, y, '0');
				world.AddEvent(this->GetName() + " kills " + o->GetName() + ".");
				break;
			}
		}
	}
}

void Sosnowskys_hogweed::draw() {
	COORD c;
	c.X = x;
	c.Y = y + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, SOS_HOG_COLOR);
	cout << "s";
	world.SetTab(x, y, 's');
}

string Sosnowskys_hogweed::GetName() {
	return "sosnowskys_hogweed";
}

void Sosnowskys_hogweed::Born(int x, int y) {
	std::vector<Organism*>& organisms = world.Getorganisms();
	organisms.push_back(new Sosnowskys_hogweed(world, x, y));
	world.SetTab(x, y, 's');
}