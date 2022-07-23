#include <iostream>
#include <string>
#include "Animal.h"
#include "World.h"

Animal::Animal(World& w, int s, int i, int x, int y) 
	:Organism(w, s, i, x, y){}

void Animal::action() {
	int move;
	bool moved = false;
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

void Animal::breeding() {
	int where;
	bool born = false;
	while (born == false) {
		where = rand() % 4;
		switch (where) {
		case UP:
			if (y > 1 && world.GetTab(x, y - 1) == '0') {
				Born(x, y-1);
				born = true;
			}
			break;
		case DOWN:
			if (y < HEIGHT && world.GetTab(x, y + 1) == '0') {
				Born(x, y+1);
				born = true;
			}
			break;
		case LEFT:
			if (x > 1 && world.GetTab(x - 1, y) == '0') {
				Born(x-1, y);
				born = true;
			}
			break;
		case RIGHT:
			if (x < WIDTH && world.GetTab(x + 1, y) == '0') {
				Born(x+1, y);
				born = true;
			}
			break;
		}
	}
	world.AddEvent("A new " + this->GetName() + " is born.");
}

void Animal::collision(int m) {//parametr m informuje z ktorego pola przyszedl organizm
	bool lost = false, turtle = false;
	if (world.GetTab(x ,y) == this->GetName()[0]) {//kolizja z organizmem tego samego typu
		bool born = false;
		if (world.GetTab(x, y - 1) == '0' || world.GetTab(x, y + 1) == '0' || world.GetTab(x - 1, y) == '0' || world.GetTab(x + 1, y) == '0') {//sprawdzanie miejsca wokó³ pierwszego organizmu
			breeding();
			born = true;
		}
		switch (m) {//organizm cofa sie na poprzednie pole
			case UP:
				if (this->GetName()[0] == 'A') y += 2;
				else y++;
				break;
			case DOWN:
				if (this->GetName()[0] == 'A') y -= 2;
				else y--;
				break;
			case LEFT:
				if (this->GetName()[0] == 'A') x += 2;
				else x++;
				break;
			case RIGHT:
				if (this->GetName()[0] == 'A') x -= 2;
				else x--;
				break;
		}
		if (born == false) {
			if (world.GetTab(x, y - 1) == '0' || world.GetTab(x, y + 1) == '0' || world.GetTab(x - 1, y) == '0' || world.GetTab(x + 1, y) == '0') {//sprawdzanie miejsca wokó³ drugiego organizmu
				breeding();
				born = true;
			}
		}
	}
	else if (world.GetTab(x, y) != '0') {
		std::vector<Organism*>& organisms = world.Getorganisms();
		for (Organism* o : organisms) {
			if (o->GetX() == this->x && o->GetY() == this->y && this != o) {
				if (o->shield(*this, m) != true) {//sprawdzanie umiejtnosci czlowieka
					if (this->GetStrength() >= o->GetStrength()) {
						if (o->defend(*this) == true) turtle = true;//sprawdzanie czy organizm jest zolwiem i sie obroni
						else {
							if (o->flee(*this) != true) {//sprawdzanie czy organizm jest antylopa i czy ucieknie
								if (o->GetName()[0] == 'G') {
									this->SetStrength(this->GetStrength() + 3);
									world.AddEvent(this->GetName() + " eats " + o->GetName() + " and his/its strength increases by 3.");
								}
								else if (o->GetName()[0] == 'g' || o->GetName()[0] == 'd') world.AddEvent(this->GetName() + " eats " + o->GetName() + ".");
								else if (o->GetName()[0] == 'b' || o->GetName()[0] == 's') {
									lost = true;
									world.AddEvent(this->GetName() + " eats " + o->GetName() + " and dies.");
								}
								else world.AddEvent(this->GetName() + " attacks and kills " + o->GetName() + ".");
								o->SetX(0);//wspolrzedne organizmu ustawiane na 0,0 by ulatwwic pozniejsze usuwanie
								o->SetY(0);
							}
						}
					}
					else {
						if (o->GetName()[0] == 'b' || o->GetName()[0] == 's') world.AddEvent(this->GetName() + " tries " + o->GetName() + " and dies.");
						else world.AddEvent(o->GetName() + " gets attacked, but kills " + this->GetName() + ".");
						lost = true;
					}
					break;
				}
			}
		}
	}

	if (turtle == true) {//cofanie na pole jesli zolw sie obronil
		switch (m) {
		case UP:
			if (this->GetName()[0] == 'A') y += 2;
			else y++;
			break;
		case DOWN:
			if (this->GetName()[0] == 'A') y -= 2;
			else y--;
			break;
		case LEFT:
			if (this->GetName()[0] == 'A') x += 2;
			else x++;
			break;
		case RIGHT:
			if (this->GetName()[0] == 'A') x -= 2;
			else x--;
			break;
		}
	}

	if(world.GetTab(x, y) != this->GetName()[0] && turtle == false){//czyszczenie tablicy 
		switch (m) {
		case UP:
			if (this->GetName()[0] == 'A') world.SetTab(x, y + 2, '0');
			else world.SetTab(x, y + 1, '0');
			break;
		case DOWN:
			if (this->GetName()[0] == 'A') world.SetTab(x, y - 2, '0');
			else world.SetTab(x, y - 1, '0');
			break;
		case LEFT:
			if (this->GetName()[0] == 'A') world.SetTab(x + 2, y, '0');
			else world.SetTab(x + 1, y, '0');
			break;
		case RIGHT:
			if (this->GetName()[0] == 'A') world.SetTab(x - 2, y, '0');
			else world.SetTab(x - 1, y, '0');
			break;
		}
		if (this->GetX() != 0 && this->GetY() != 0) world.SetTab(x, y, this->GetName()[0]);
	}

	if (lost == true) {//zerowanie wspolrzednych atakujacego  przypadku przegranej
		this->SetX(0);
		this->SetY(0);
	}
}

