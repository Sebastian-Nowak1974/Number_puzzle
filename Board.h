#pragma once

#include <cassert>
#include <array>

#include "Random.h"
#include "Point.h"
#include "Texture.h"
#include "Shader.h"

class Board
{
public:
    Board() = default;

    // finds coordinates of empty tile
    Point emptyTile();

    // moves a tile by swapping an adjacent tile with empty one
    bool moveTile(Direction dir);
    void renderBoard(const Texture& texture, GLFWwindow* window, const Shader& shader, float time = 0.0f);        
    void Randomize();
    bool puzzleSolved();
    friend bool operator==(const Board& b1, const Board& b2);
    
private:
    static const int s_size{ 4 };
    int  m_tiles[s_size][s_size]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0 };
};