#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


//valgrind
enum class Keys{ UP, DOWN, RIGHT, LEFT };
enum class Color {RED, BLUE, PURPLE, ORANGE, YELLOW};


class MoveableSquare{
private:
    int coord; //coordinate of the square for the graph
    Keys direction;
    Color color;
    int centre[2];
    glm::vec3 vertices[4];
public: 
    unsigned int VAO, VBO, EBO;

    MoveableSquare(float , float, float, float, float, float, float, float);

    const int getCoord();
    const glm::vec3* getVertices();
    const int* getCentre();
    const Keys getDirection();
    const Color getColor();

    void setCentre(); //for now it updates the center to coordiantes of the square.
    void setDirection(Keys);
    void setColor(Color);
    void setVertices(int,double,double,double);

    void loadSquare();
    void drawSquare();

    void deleteVertexetBuff();
};