#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

//valgrind


class MoveableSquare {
private:
    int coord; //coordinate of the square for the graph
    GLfloat* vertices = new GLfloat[9];
public: 
    unsigned int VAO, VBO;

    MoveableSquare();
    int getCoord();

    void loadSquare();
    void drawSquare();
    void move(int);

    void deleteVertexetBuff();
};