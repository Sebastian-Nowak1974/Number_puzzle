/* This program is a 15 numbers puzzle. It consists of 4x4 grid with numbers and one empty space.
   Tiles with numbers on are moved by pressing 'w', 's', 'a' and 'd' keys. The aim is to put 
   numbers in order, with empty tile last. Game board is rendered with OpenGL.
*/

#include "Texture.h"
#include "Shader.h"
#include "Point.h"
#include "Board.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
Direction keyToDirection(GLFWwindow* window);
bool keyAction(GLFWwindow* window, Board& board);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{        
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
           
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    float vertices[]{
          0.24f,  0.24f, 0.0f, 1.0f, 1.0f, // upright corner
          0.24f, -0.24f, 0.0f, 1.0f, 0.0f,  // downright
         -0.24f,  0.24f, 0.0f, 0.0f, 1.0f, // upleft
         -0.24f, -0.24f, 0.0f, 0.0f, 0.0f // downleft         
    };
    unsigned int indices[]{
        2, 1 , 0,
        2, 1, 3
    };

    GLuint VBO{};
    GLuint VAO{};
    GLuint EBO{};
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO);    

        
    
    const char* texture1Files[]{ "empty.jpg", "one.jpg", "two.jpg", "three.jpg", "four.jpg",
                       "five.jpg", "six.jpg", "seven.jpg", "eight.jpg", "nine.jpg",
                       "ten.jpg", "eleven.jpg", "twelve.jpg", "thirteen.jpg",
                       "fourteen.jpg", "fifteen.jpg"};    

    int texture1Size{ sizeof(texture1Files) / sizeof(texture1Files[0]) };
    Texture texture1{ texture1Size, texture1Files };

    const char* texture2Files[]{"empty.jpg", "w.jpg", "e.jpg", "l.jpg", "l.jpg", "d.jpg", "o.jpg", "n.jpg",
                                "e.jpg", "exclamation.jpg","exclamation.jpg", "exclamation.jpg",
                                "blue.jpg", "blue.jpg", "blue.jpg", "blue.jpg" };

    int texture2Size{ sizeof(texture2Files) / sizeof(texture2Files[0]) };
    Texture texture2{ texture2Size, texture2Files };

    Shader shader;
    shader.useProgram();
       
    Board board;

    // "mixing" puzzle elements, ready to play
    board.Randomize(); 
    
    float T{};
    float t{};
    bool gameOver{false};
    constexpr float angularSpeed{ 1.3f};
    constexpr float pi{ 3.14f };
    
    while (!glfwWindowShouldClose(window)) {
        
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if(keyAction(window, board))
            gameOver = board.puzzleSolved();

        if (!gameOver)
        {
            T = glfwGetTime();                       
            board.renderBoard(texture1, window, shader);
        }
        else
        {
            t = glfwGetTime() - T;
            if (t < pi/(2 * angularSpeed))
                board.renderBoard(texture1, window, shader, angularSpeed * t);

            else if (t >= pi / (2 * angularSpeed) && t < pi/angularSpeed)
                board.renderBoard(texture2, window, shader, angularSpeed * t);

            else
                board.renderBoard(texture2, window, shader, pi);

        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shader.deleteShader();    
    glfwTerminate();
    return 0;
}



void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{    
    glViewport(0, 0, width, height);
}

Direction keyToDirection(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        return Direction::up;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        return Direction::down;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        return Direction::left;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        return Direction::right;

    return Direction::maxDirections;
}

// moves a tile by pressing w, s, a or d key 
bool keyAction(GLFWwindow* window, Board& board)
{    
    Direction::Type direction = keyToDirection(window).getType();
    static bool keyReleased{ true };
    
    if (direction != Direction::maxDirections)
    {
        if (keyReleased)
        {                
            keyReleased = false;
            return board.moveTile(direction);
        }        
    }
    else
        keyReleased = true;
    
    return false;
}
