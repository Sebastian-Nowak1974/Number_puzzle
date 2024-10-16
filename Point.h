#pragma once

#include <iostream>
#include "Direction.h"
struct Point
{
	int x{};
	int y{};

	friend bool operator==(Point p1, Point p2);
	friend bool operator!=(Point p1, Point p2);

	// gets points adjacent to empty tile
	Point getAdjacentPoint(Direction dir) const;
};