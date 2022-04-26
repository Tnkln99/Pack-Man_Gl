#include "../headers/Square.h"

Square::Square(float centerx, float centery, float size) 
{
    vertices[0] = glm::vec3(centerx + size,  centery + size, 0.0f); // top right // 0
    vertices[1] = glm::vec3(centerx + size, centery - size, 0.0f);  // bottom right // 1
    vertices[2] = glm::vec3(centerx - size, centery - size, 0.0f);  // bottom left // 2
    vertices[3] =  glm::vec3(centerx - size,  centery + size, 0.0f);  // top left  // 3
	this->loadSquare();
}

const int Square::getCoord()
{
    return this->coord;
}

const glm::vec3* Square::getVertices(){
	return this->vertices;
}

const Color Square::getColor(){
	return this->color;
}

void Square::setColor(Color C){
	color = C;
}


void Square::setVertices(int i,double x,double y, double z){
	vertices[i].x = x;
	vertices[i].y = y;
	vertices[i].z = z;
}

void Square::loadSquare()
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
 
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

void Square::drawSquare()
{
	// Bind the VAO so OpenGL knows to use it
	glBindVertexArray(VAO);
	// Draw the triangle using the GL_TRIANGLES primitive
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Square::deleteVertexetBuff(){
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
