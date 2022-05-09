#include "../headers/Wall.h"

Wall::Wall(int indice, GLint shaderProgram) : Square(indiceToCoordinate(indice).first, indiceToCoordinate(indice).second, 0.02f, shaderProgram){
    Square::setColor(Color::PURPLE);
}