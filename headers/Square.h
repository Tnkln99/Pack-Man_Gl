#pragma once
#include <stdio.h>
#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "enumerations.h"
#include <utility>
#include <iostream>


//valgrind


class Square{
private:
    Color color;
protected:
    glm::vec3 vertices[4];
    std::pair<float,float> center; //position as x and y
public: 
    unsigned int VAO, VBO, EBO;
    GLint shaderProgram;

    Square(float, float, float, GLint shaderProgram);

    const std::pair<float,float> indiceToCoordinate(int);
    const int coordinateToIndice(float,float);

    const glm::vec3* getVertices();
    const Color getColor();
    const std::pair<float,float> getCenter();
    const GLint getShaderProgram();

    void setColor(Color);
    void setVertices(int,double,double,double);
    virtual void setCenter(float,float);

    void colorToRGB(Color,float*);

    void loadSquare();
    void drawSquare();

    void deleteVertexetBuff();
};