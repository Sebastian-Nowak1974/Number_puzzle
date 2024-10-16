#include "Direction.h"

Direction Direction::operator-() const
{
    switch (m_type)
    {
    case up:    return Direction{ down };
    case down:  return Direction{ up };
    case left:  return Direction{ right };
    case right: return Direction{ left };
    default:    break;
    }

    assert(0 && "Unsupported direction was passed!");
    return Direction{ up };
}

