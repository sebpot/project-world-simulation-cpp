#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <conio.h>
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

#define Z 122
#define N 110
#define S 115
#define ARROWS 224

using namespace std;

int main() {
	int input;
	bool move = true;
	srand (time(NULL));
	vector<Organism*>organisms;
	World world(organisms, WIDTH, HEIGHT);
	cout << "Press n to create a new world or l to load a world from file.";
	input = _getch();
	if (input == N) world.newworld();
	else world.load();
	world.Clear();
	world.DrawWorld();
	while (input != Z) {
		input = _getch();
		if (input == Z) {
			world.save();
			break;
		}
		else if (input == ARROWS || input == S) {
			if(input == ARROWS) input = _getch();
			for (Organism* o : organisms) {
				if (dynamic_cast<Human*>(o)) {
					if (o->GetSpecial() != 0 && input == Z) move = false;
					else move = true;
					o->setmove(input);//ruch cz³owieka
				}
			}
			if (move == true) {
				world.Clear();
				world.Move();
				world.DrawWorld();
			}
		}
	}
	return 0;
}