#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <vector>
#include <algorithm>
#include <windows.h> 
#include "World.h"
#include "Human.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"
#include "Grass.h"
#include "Dandelion.h"
#include "Guarana.h"
#include "Belladonna.h"
#include "Sosnowskys_hogweed.h"

#define WHITE 15

using namespace std;

World::World(vector<Organism*>&o, int w, int h)
	:organisms(o), width(w), height(h), eventscount(0){}

void World::DrawWorld() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, WHITE);
	COORD c;
	c.X = 0;
	c.Y = 0;
	cout << "Sebastian Potrykus 184308\n\n";
	for (int k = 0; k < width + 2; k++) cout << "#";
	cout << "\n";
	for (int i = 1; i < height+1; i++) {
		cout << "#";
		for (int j = 1; j < width+1; j++) {
			cout << " ";
			tab[i][j] = '0';
		}
		cout << "#\n";
	}
	for (int i = 0; i < width + 2; i++) cout << "#";

	c.X = width+15;
	c.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	cout<<"Events:";
	if (eventscount <= 25) {
		for (int i = 1; i < eventscount + 1; i++) {
			c.X = width + 15;
			c.Y = i;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << i << ")" << events[i - 1];
		}
	}
	else {
		while (events.size() != 25) events.erase(events.begin());//jesli ilosc zdarzen przekracza 25 usuwane s¹ elementy wektora
		for (int i = 0; i < 25; i++) {
			c.X = width + 15;
			c.Y = i + 1;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << eventscount - 24 + i << ")" << events[i];
		}
	}

	for (Organism* o : organisms) {
		o->draw();
	}
	SetConsoleTextAttribute(hConsole, WHITE);
	c.X = 0;
	c.Y = height+5;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	cout << "Press arrows to move human or s to use Alzur's shield";
	c.X = 0;
	c.Y = height + 6;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	cout << "Press z to save world and end program";
	c.X = 0;
	c.Y = height + 7;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

	for (Organism* o : organisms) {//informacja o umiejetnosci specjalnej
		if (o->GetName()[0] == 'H') {
			if (o->GetSpecial() == 0) cout << "Alzur's shield is inactive.";
			else if (o->GetSpecial() > 0) cout << "Alzur's shield will be activated for another " << o->GetSpecial() << " rounds.";
			else cout << "Alzur's shield can't be used for another " << -o->GetSpecial() << " rounds.";
			break;
		}
	}
	c.X = 0;
	c.Y = height + 8;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void World::Clear() {
	system("cls");
}

void World::Move() {
	stable_sort(organisms.begin(), organisms.end(),//sortowanie organizmow
		[](Organism* a, Organism* b) {
			return a->GetInitiative() > b->GetInitiative();
		});
	int length = organisms.size();
	for (int i = 0; i < length; i++) {
		if(organisms[i]->GetX() != 0 && organisms[i]->GetY() != 0) organisms[i]->action();
	}
	length = organisms.size();
	for (int i = length - 1; i >= 0; i--) {
		if (organisms[i]->GetName()[0] == 'H') {//aktualizowanie umiejetnosci specjalnej
			if (organisms[i]->GetSpecial() > 0) {
				organisms[i]->SetSpecial(organisms[i]->GetSpecial() - 1);
				if (organisms[i]->GetSpecial() == 0) organisms[i]->SetSpecial(-5);
			}
			else if(organisms[i]->GetSpecial() < 0) organisms[i]->SetSpecial(organisms[i]->GetSpecial() + 1);
		}

		if (organisms[i]->GetX() == 0 && organisms[i]->GetY() == 0) {
			organisms.erase(organisms.begin() + i);
		}
	}
}

vector<Organism*>& World::Getorganisms() {
	return organisms;
}

void World::AddEvent(string newevent) {
	events.push_back(newevent);
	eventscount++;
}

char World::GetTab(int x, int y) {
	return tab[y][x];
}

void World::SetTab(int x, int y, char organism) {
	tab[y][x] = organism;
}

void World::newworld() {
	//organisms.push_back(new Human(*this, 20, 10, 0));
	//organisms.push_back(new Wolf(*this, 6, 16));
	//organisms.push_back(new Wolf(*this, 3, 12));
	//organisms.push_back(new Sheep(*this, 15, 6));
	//organisms.push_back(new Sheep(*this, 17, 3));
	//organisms.push_back(new Fox(*this, 10, 10));
	//organisms.push_back(new Fox(*this, 30, 18));
	//organisms.push_back(new Turtle(*this, 31, 14));
	//organisms.push_back(new Turtle(*this, 6, 2));
	organisms.push_back(new Antelope(*this, 36, 1));
	organisms.push_back(new Antelope(*this, 36, 5));
	//organisms.push_back(new Grass(*this, 20, 18));
	//organisms.push_back(new Dandelion(*this, 2, 4));
	//organisms.push_back(new Guarana(*this, 17, 15));
	//organisms.push_back(new Belladonna(*this, 2, 2));
	organisms.push_back(new Sosnowskys_hogweed(*this, 15, 9));
	organisms.push_back(new Sosnowskys_hogweed(*this, 15, 10));
}

void World::save() {
	FILE* file;
	file = fopen("world.txt", "w");
	for (Organism* o : organisms) {
		if (o->GetName()[0] == 'H') fprintf(file, "%c %d %d %d %d\n", o->GetName()[0], o->GetStrength(), o->GetX(), o->GetY(), o->GetSpecial());
		else fprintf(file, "%c %d %d %d\n", o->GetName()[0], o->GetStrength(), o->GetX(), o->GetY());
	}
	fprintf(file, "%c", 'E');
	fclose(file);
}

void World::load() {
	char organism;
	int strength, x, y, special;
	FILE* file;
	file = fopen("world.txt", "r");
	do {
		fscanf(file, "%c %d %d %d %d", &organism, &strength, &x, &y, &special);
		if (organism == 'E') break;
		switch (organism) {
		case 'A':
			organisms.push_back(new Antelope(*this, x, y));
			organisms[organisms.size() - 1]->SetStrength(strength);
			break;
		case 'F':
			organisms.push_back(new Fox(*this, x, y));
			organisms[organisms.size() - 1]->SetStrength(strength);
			break;
		case 'H':
			organisms.push_back(new Human(*this, x, y, special));
			organisms[organisms.size() - 1]->SetStrength(strength);
			break;
		case 'S':
			organisms.push_back(new Sheep(*this, x, y));
			organisms[organisms.size() - 1]->SetStrength(strength);
			break;
		case 'T':
			organisms.push_back(new Turtle(*this, x, y));
			organisms[organisms.size() - 1]->SetStrength(strength);
			break;
		case 'W':
			organisms.push_back(new Wolf(*this, x, y));
			organisms[organisms.size() - 1]->SetStrength(strength);
			break;
		case 'b':
			organisms.push_back(new Belladonna(*this, x, y));
			break;
		case 'd':
			organisms.push_back(new Dandelion(*this, x, y));
			break;
		case 'g':
			organisms.push_back(new Grass(*this, x, y));
			break;
		case 'G':
			organisms.push_back(new Guarana(*this, x, y));
			break;
		case 's':
			organisms.push_back(new Sosnowskys_hogweed(*this, x, y));
			break;
		}
	} while (organism != 'E');
	fclose(file);
}

World::~World() {
	organisms.clear();
}

