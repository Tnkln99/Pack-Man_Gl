#include <stdio.h>
#include "../headers/moveableSquare.h"

MoveableSquare::MoveableSquare() 
{
    // Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	this->loadSquare();
}

int MoveableSquare::getCoord()
{
    return this->coord;
}

void MoveableSquare::loadSquare()
{
	unsigned int indices[] = {  
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
     
    // bind vertex array object
    glBindVertexArray(VAO);
 
    // bind vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
    // bind element buffer objects
    // EBO is stored in the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
 
    // registered VBO as the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
 
    // unbind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void MoveableSquare::drawSquare()
{
	// Bind the VAO so OpenGL knows to use it
	glBindVertexArray(VAO);
	// Draw the triangle using the GL_TRIANGLES primitive
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void MoveableSquare::deleteVertexetBuff(){
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void MoveableSquare::move(int destination)
{
	this->coord = destination;
	// all the moving functions will be implemented here
}