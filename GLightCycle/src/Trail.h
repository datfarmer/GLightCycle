/*
 * Trail.h
 *
 *  Created on: Oct 26, 2011
 *      Author: kimsj
 */

#ifndef TRAIL_H_
#define TRAIL_H_

#include "Coords.h"
#include <vector>

class Trail {

	int ID;
public:
	std::vector<Coords> points;
	Trail();
	Trail(Coords, int);
	virtual ~Trail();
	void addPoint(Coords);
	std::vector<Coords> *getPoints();
	void setPoints(std::vector<Coords>);
	void clear();
	int getID();
};

#endif /* TRAIL_H_ */
