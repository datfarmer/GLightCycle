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
	std::vector<Coords> points;
	int ID;
public:
	Trail();
	Trail(Coords, int);
	virtual ~Trail();
	void addPoint(Coords);
	std::vector<Coords> getPoints();
	int getID();
};

#endif /* TRAIL_H_ */
