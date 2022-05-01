#pragma once
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "enumerations.h"
#include <utility>


//valgrind


class Square{
private:
    Color color;
protected:
    glm::vec3 vertices[4];
    std::pair<float,float> center; //position as x and y
public: 
    unsigned int VAO, VBO, EBO;

    Square(float, float, float);

    const glm::vec3* getVertices();
    const Color getColor();
    const std::pair<float,float> getCenter();

    void setColor(Color);
    void setVertices(int,double,double,double);
    void setCenter(float,float);

    void loadSquare();
    void drawSquare();

    void deleteVertexetBuff();
};