#include <iostream>
#include <windows.h> 
#include "Human.h"
#include "World.h"
#define HUMAN_COLOR 23
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define S 115

using namespace std;

Human::Human(World& w, int x, int y, int s)
	:Animal(w, 5, 4, x, y) {
	special = s;
}

void Human::action() {
	switch (move) {
	case KEY_UP:
		if (y > 1) {
			y--;
			collision(UP);
		}
		break;
	case KEY_DOWN:
		if (y < HEIGHT) {
			y++;
			collision(DOWN);
		}
		break;
	case KEY_LEFT:
		if (x > 1) {
			x--;
			collision(LEFT);
		}
		break;
	case KEY_RIGHT:
		if (x < WIDTH) {
			x++;
			collision(RIGHT);
		}
		break;
	}
}

void Human::setmove(int m) {
	this->move = m;
	if(m == S)
		if (special == 0) special = 5;
}

void Human::draw() {
	COORD c;
	c.X = x;
	c.Y = y+2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, HUMAN_COLOR);
	cout << "H";
	world.SetTab(x, y, 'H');
}

string Human::GetName() {
	return "Human";
}

void Human::Born(int x, int y){}

bool Human::shield(Organism& attacker, int m) {
	bool moved = false;
	int move;
	if (special > 0) {//sprawdzanie aktywnosci umiejetnosci
		if (world.GetTab(attacker.GetX(), attacker.GetY() - 1) == '0' || world.GetTab(attacker.GetX(), attacker.GetY() + 1) == '0' || world.GetTab(attacker.GetX() - 1, attacker.GetY()) == '0' || world.GetTab(attacker.GetX() + 1, attacker.GetY()) == '0') {//sprawdzenie czy atakujacy organizm ma wwolne pole do przesuniecia
			switch (m) {//usuniecie poprzedniego miejsca pobytu organizmu
			case UP:
				if (attacker.GetName()[0] != 'A') world.SetTab(attacker.GetX(), attacker.GetY() + 1, '0');
				else world.SetTab(attacker.GetX(), attacker.GetY() + 2, '0');
				break;
			case DOWN:
				if (attacker.GetName()[0] != 'A') world.SetTab(attacker.GetX(), attacker.GetY() - 1, '0');
				else world.SetTab(attacker.GetX(), attacker.GetY() - 2, '0');
				break;
			case LEFT:
				if (attacker.GetName()[0] != 'A') world.SetTab(attacker.GetX() + 1, attacker.GetY(), '0');
				else world.SetTab(attacker.GetX() + 2, attacker.GetY(), '0');
				break;
			case RIGHT:
				if (attacker.GetName()[0] != 'A') world.SetTab(attacker.GetX() - 1, attacker.GetY(), '0');
				else world.SetTab(attacker.GetX() - 2, attacker.GetY(), '0');
				break;
			}
			
			while (moved == false) {//ruch organizmu na wolne pole(przesuniecie)
				move = rand() % 4;
				switch (move) {
				case UP:
					if (world.GetTab(attacker.GetX(), attacker.GetY() - 1) == '0') {
						attacker.SetY(attacker.GetY() - 1);
						world.SetTab(attacker.GetX(), attacker.GetY(), attacker.GetName()[0]);
						moved = true;
					}
					break;
				case DOWN:
					if (world.GetTab(attacker.GetX(), attacker.GetY() + 1) == '0') {
						attacker.SetY(attacker.GetY() + 1);
						world.SetTab(attacker.GetX(), attacker.GetY(), attacker.GetName()[0]);
						moved = true;
					}
					break;
				case LEFT:
					if (world.GetTab(attacker.GetX() - 1, attacker.GetY()) == '0') {
						attacker.SetX(attacker.GetX() - 1);
						world.SetTab(attacker.GetX(), attacker.GetY(), attacker.GetName()[0]);
						moved = true;
					}
					break;
				case RIGHT:
					if (world.GetTab(attacker.GetX() + 1, attacker.GetY()) == '0') {
						attacker.SetX(attacker.GetX() + 1);
						world.SetTab(attacker.GetX(), attacker.GetY(), attacker.GetName()[0]);
						moved = true;
					}
					break;
				}
			}
		}
		else {//jesli brak miejsca wokol czlowieka organizm cofa sie na swoje poprzednie pole
			switch (m) {
			case UP:
				if (attacker.GetName()[0] == 'A') attacker.SetY(attacker.GetY() + 2);
				else attacker.SetY(attacker.GetY() + 1);
				world.SetTab(attacker.GetX(), attacker.GetY(), attacker.GetName()[0]);
				break;
			case DOWN:
				if (attacker.GetName()[0] == 'A') attacker.SetY(attacker.GetY() - 2);
				else attacker.SetY(attacker.GetY() - 1);
				world.SetTab(attacker.GetX(), attacker.GetY(), attacker.GetName()[0]);
				break;
			case LEFT:
				if (attacker.GetName()[0] == 'A') attacker.SetX(attacker.GetX() + 2);
				else attacker.SetX(attacker.GetX() + 1);
				world.SetTab(attacker.GetX(), attacker.GetY(), attacker.GetName()[0]);
				break;
			case RIGHT:
				if (attacker.GetName()[0] == 'A') attacker.SetX(attacker.GetX() - 2);
				else attacker.SetX(attacker.GetX() - 1);
				world.SetTab(attacker.GetX(), attacker.GetY(), attacker.GetName()[0]);
				break;
			}
		}
		world.AddEvent(attacker.GetName() + " attacks, but " + this->GetName() + " uses Alzur's shield.");
		return true;
	}
	else return false;
}

int Human::GetSpecial() {
	return special;
}

void Human::SetSpecial(int s) {
	special = s;
}