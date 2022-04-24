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

glm::vec3* MoveableSquare::getVertices(){
	return this->vertices;
}

void MoveableSquare::setVerticles(glm::vec3 vec, int indice){
	this->vertices[indice] = vec;
}

void MoveableSquare::loadSquare()
{
	direction = Keys::UP;
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
 
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

void MoveableSquare::setDirection(Keys K)
{
	direction = K;
}

void MoveableSquare::update(){
	drawSquare();
	glm::mat4 trans = glm:: mat4(1.0f);
	if(direction == Keys::UP)
		trans = glm::translate(trans, glm::vec3(0.0f, 0.0001f, 0.0f));
	else if (direction == Keys::LEFT)
		trans = glm::translate(trans, glm::vec3(-0.0001f, 0.0f, 0.0f));
	else if (direction == Keys::DOWN)
		trans = glm::translate(trans, glm::vec3(0.0f, -0.0001f, 0.0f));
	else if (direction == Keys::RIGHT)
		trans = glm::translate(trans, glm::vec3(0.0001f, 0.0f, 0.0f));
	
	for(int i=0; i < 4; i ++){
		glm::vec4 tmp = trans * glm::vec4(vertices[i],1);
		vertices[i].x = tmp.x;
		vertices[i].y = tmp.y;
		vertices[i].z = tmp.z;
	}

	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW); 
}