#include "../headers/Wall.h"

Wall::Wall(int indice) : Square(indiceToCoordinate(indice).first, indiceToCoordinate(indice).second, 0.02f){
    Square::setColor(Color::PURPLE);
}