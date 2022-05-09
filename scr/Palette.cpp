#include "../headers/Palette.h"

Palette::Palette(int indice, GLint shaderProgram) : Square(indiceToCoordinate(indice).first, indiceToCoordinate(indice).second, 0.005f, shaderProgram){
    coord = indice;
    Square::setColor(Color::WHITE);
}

const int Palette::getCoord(){
    return coord;
}

void Palette::setCoord(int i){
    coord = i;
}