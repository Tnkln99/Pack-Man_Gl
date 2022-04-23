#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

//valgrind


class MoveableSquare {
private:
    int coord; //coordinate of the square for the graph
    glm::vec3 vertices[4] = {
       glm::vec3(0.1f,  0.1f, 0.0f),  // top right // 0
       glm::vec3(0.1f, -0.1f, 0.0f),  // bottom right // 1
       glm::vec3(-0.1f, -0.1f, 0.0f),  // bottom left // 2
       glm::vec3(-0.1f,  0.1f, 0.0f)   // top left  // 3
    };
public: 
    unsigned int VAO, VBO, EBO;

    MoveableSquare();
    int getCoord();

    void loadSquare();
    void drawSquare();
    void move(int);

    void deleteVertexetBuff();
};