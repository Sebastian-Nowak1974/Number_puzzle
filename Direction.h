#pragma once

#include <cassert>
#include "Random.h"

class Direction
{
public:
    enum Type
    {
        up,
        down,
        left,
        right,
        maxDirections,
    };

    Direction(Type type)
        :m_type(type)
    {
    }

    inline Type getType() const { return m_type; }
    Direction operator-() const;
    static Type getRandomDirection()
    {
        Direction::Type random{ static_cast<Direction::Type>(Random::get(0, Direction::maxDirections - 1)) };
        return random;
    }

private:
    Type m_type;
};
