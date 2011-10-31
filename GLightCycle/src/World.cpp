/*
 * World.cpp
 *
 *  Created on: Oct 26, 2011
 *      Author: kimsj
 */

#include "Cycle.h"
#include "Trail.h"
#include "World.h"
#include "Coords.h"
using namespace std;

World::World(int w, int h, int n) {
	// TODO Auto-generated constructor stub
	width = w;
	height = h;
	numPlayers = n;
}

World::~World() {
	// TODO Auto-generated destructor stub
}

Cycle *World::getCycles() {
	return cycles;
}

std::vector<WorldItem> World::getItems() {
	return items;
}

int World::getNumPlayers() {
	return numPlayers;
}

Trail *World::getTrails() {
	return trails;
}

int World::getWidth()
{
	return width;
}

void World::setNumPlayers(int np)
{
	numPlayers = np;
}
