#include <iostream>
#include "Organism.h"

Organism::Organism(World& w, int s, int i, int x, int y) 
	: world(w), strength(s), initiative(i), x(x), y(y){}

void Organism::setmove(int m){}

int Organism::GetX() { return x; }

int Organism::GetY() { return y; }

int Organism::GetStrength() { return strength; }

int Organism::GetInitiative() { return initiative; }

void Organism::SetX(int x_new) { this->x = x_new; }

void Organism::SetY(int y_new) { this->y = y_new; }

void Organism::SetStrength(int s) { this->strength = s; }

bool Organism::defend(Organism& attacker) { return false; }

bool Organism::flee(Organism& attacker) { return false; }

bool Organism::shield(Organism& attacker, int m) { return false; }

int Organism::GetSpecial() { return 0; }

void Organism::SetSpecial(int s) {}
