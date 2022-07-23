#pragma once
#include "Organism.h"
#include <vector>
#include <string>
#define WIDTH 40
#define HEIGHT 20
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3


class World {
private:	
	const int width, height;
	std::vector<Organism*>&organisms;
	std::vector<std::string>events;
	int eventscount;
	char tab[HEIGHT + 1][WIDTH + 1];
public:
	World(std::vector<Organism*>&o, int w,int h);
	void DrawWorld();
	void Clear();
	void Move();
	std::vector<Organism*>& Getorganisms();
	void AddEvent(std::string newevent);
	char GetTab(int x, int y);
	void SetTab(int x, int y, char organism);
	void newworld();
	void save();
	void load();
	~World();
};
