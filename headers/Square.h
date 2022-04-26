#pragma once
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "enumerations.h"


//valgrind


class Square{
private:
    int coord; //coordinate of the square for the graph
    Color color;
    int centre[2];
    glm::vec3 vertices[4];
public: 
    unsigned int VAO, VBO, EBO;

    Square(float, float, float);

    const int getCoord();
    const glm::vec3* getVertices();
    const int* getCentre();
    
    const Color getColor();

    void setColor(Color);
    void setVertices(int,double,double,double);

    void loadSquare();
    void drawSquare();

    void deleteVertexetBuff();
};