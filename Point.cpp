#include "Point.h"

bool operator==(Point p1, Point p2)
{
    return p1.x == p2.x && p1.y == p2.y;

}
bool operator!=(Point p1, Point p2)
{
    return !(p1 == p2);
}

Point Point::getAdjacentPoint(Direction dir) const
{
    switch (dir.getType())
    {
    case Direction::up:     return Point{ x,     y - 1 };
    case Direction::down:   return Point{ x,     y + 1 };
    case Direction::left:   return Point{ x - 1, y };
    case Direction::right:  return Point{ x + 1, y };
    default:                break;
    }

    assert(0 && "Unsupported direction was passed!");
    return *this;
}