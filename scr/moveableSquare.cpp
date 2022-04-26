#include "../headers/moveableSquare.h"

MoveableSquare::MoveableSquare(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) 
{
    vertices[0] = glm::vec3(x1,  y1, 0.0f); // top right // 0
    vertices[1] = glm::vec3(x2, y2, 0.0f);  // bottom right // 1
    vertices[2] = glm::vec3(x3, y3, 0.0f);  // bottom left // 2
    vertices[3] =  glm::vec3(x4,  y4, 0.0f);  // top left  // 3 
	this->loadSquare();
}

const int MoveableSquare::getCoord()
{
    return this->coord;
}

const glm::vec3* MoveableSquare::getVertices(){
	return this->vertices;
}

void MoveableSquare::setCentre(){
    centre[0] = (getVertices()[0].x + getVertices()[3].y) / 2;
    centre[1] = (getVertices()[0].x + getVertices()[1].y) / 2;
}

const Keys MoveableSquare::getDirection(){
	return this->direction;
}

const Color MoveableSquare::getColor(){
	return this->color;
}

void MoveableSquare::setDirection(Keys K){
	direction = K;
}

void MoveableSquare::setColor(Color C){
	color = C;
}

void MoveableSquare::setVertices(int i,double x,double y, double z){
	vertices[i].x = x;
	vertices[i].y = y;
	vertices[i].z = z;
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

