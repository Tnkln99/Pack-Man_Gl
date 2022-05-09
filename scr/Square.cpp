#include "../headers/Square.h"

Square::Square(float centerx, float centery, float size, GLint shaderProgram) 
{
    this->shaderProgram = shaderProgram;
    center.first = centerx;
    center.second = centery;
    vertices[0] = glm::vec3(centerx + size,  centery + size, 0.0f); // top right // 0
    vertices[1] = glm::vec3(centerx + size, centery - size, 0.0f);  // bottom right // 1
    vertices[2] = glm::vec3(centerx - size, centery - size, 0.0f);  // bottom left // 2
    vertices[3] =  glm::vec3(centerx - size,  centery + size, 0.0f);  // top left  // 3
	this->loadSquare();
}

const std::pair<float,float> Square::indiceToCoordinate(int indice){
    float x = -1.0f + ((indice % 40) * 0.04f) + 0.02f;
    float y = 1.0f - ((indice / 40) * 0.04f) - 0.02f;
    return std::pair<float,float>(x,y);
}

const int Square::coordinateToIndice(float x,float y){

    std::cout<<"x: "<<x<<" y: "<<y<<std::endl;
    int cptx = 0; // j
    while(x - 0.02f >= -1.0f){
        x -= 0.04f;
        ++cptx;
    }
    int cpty = 0; // i
    while(y + 0.02f <= 1.0f){
        y += 0.04f;
        ++cpty;
    }
    std::cout<<"cptx: "<<cptx<<" cpty: "<<cpty<<std::endl;
    return cpty * 40 + cptx;
}

const glm::vec3* Square::getVertices(){
	return this->vertices;
}

const Color Square::getColor(){
	return this->color;
}

const std::pair<float,float> Square::getCenter(){
    return this->center;;
}

void Square::setColor(Color C){
	color = C;
}

void Square::setVertices(int i,double x,double y, double z){
	vertices[i].x = x;
	vertices[i].y = y;
	vertices[i].z = z;
}

void Square::setCenter(float x, float y){
    center.first = x;
    center.second = y;
}

void Square::colorToRGB(Color C, float* rgb){
    switch(C){
        case Color::RED:
            rgb[0] = 1.0f;
            rgb[1] = 0.0f;
            rgb[2] = 0.0f;
            break;
        case Color::PURPLE:
            rgb[0] = 0.5f;
            rgb[1] = 0.0f;
            rgb[2] = 0.5f;
            break;
        case Color::BLUE:
            rgb[0] = 0.0f;
            rgb[1] = 0.0f;
            rgb[2] = 1.0f;
            break;
        case Color::YELLOW:
            rgb[0] = 1.0f;
            rgb[1] = 1.0f;
            rgb[2] = 0.0f;
            break;
        case Color::WHITE:
            rgb[0] = 1.0f;
            rgb[1] = 1.0f;
            rgb[2] = 1.0f;
            break;
        case Color::ORANGE:
            rgb[0] = 1.0f;
            rgb[1] = 0.5f;
            rgb[2] = 0.0f;
            break;
    };
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
    GLint colorLocation = glGetUniformLocation(shaderProgram, "my_color");
    float rgb[3];
    colorToRGB(color,rgb);
    glUniform3fv(colorLocation, 1, rgb);  

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

