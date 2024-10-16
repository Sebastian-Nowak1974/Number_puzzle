#include "Board.h"

Point Board::emptyTile()
{
    for (int y = 0; y < s_size; ++y)
    {
        for (int x = 0; x < s_size; ++x)
        {
            if (m_tiles[y][x] == 0)
                return Point{ x, y };
        }
    }
    assert(0 && "There is no empty tile in the board!!!");
    return { -1,-1 };
}

bool Board::moveTile(Direction dir)
{        
    Point empty{ emptyTile() };
    Point adj{ empty.getAdjacentPoint((-dir).getType()) };
    if (adj.x >= 0 && adj.y >= 0 && adj.x < s_size && adj.y < s_size)
    {        
        std::swap(m_tiles[empty.y][empty.x], m_tiles[adj.y][adj.x]);           
        return true;
    }
    else
        return false;
}

void Board::Randomize()
{
    for (int i{ 0 };i < 1000; )
    {       
        if (Board::moveTile(Direction::getRandomDirection()))
            ++i;
    }
}

void Board::renderBoard(const Texture& texture, GLFWwindow* window, const Shader& shader, float t)
{        
    glm::mat4 transform{};
    glm::vec3 translationVector{};
    unsigned int transformLoc{};
    
    for (int y = 0; y < s_size; ++y)
    {
        for (int x = 0; x < s_size; ++x)
        {              
            translationVector = glm::vec3(0.5 * static_cast<float>(x) - 0.75f,
                                -0.5 * static_cast<float>(y) + 0.75f, 0.0f);            
            transform = glm::mat4(1.0f);           
            transform = glm::translate(transform, translationVector);
            transform = glm::rotate(transform, t, glm::vec3(1.0f, 0.0f, 0.0f));            
            
            transformLoc = glGetUniformLocation(shader.getShaderID(), "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
           
            texture.bindTexture(m_tiles[y][x]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
} 

bool operator==(const Board& b1, const Board& b2)
{
    for (int y = 0; y < b1.s_size; ++y)
    {
        for (int x = 0; x < b1.s_size; ++x)
        {
            if (b1.m_tiles[y][x] != b2.m_tiles[y][x])
                return 0;
        }
    }
    return 1;
}

bool Board::puzzleSolved()
{    
    static Board s_board{};
    return s_board == *this;
}