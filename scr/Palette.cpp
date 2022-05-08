#include "../headers/Palette.h"

Palette::Palette(int indice) : Square(indiceToCoordinate(indice).first, indiceToCoordinate(indice).second, 0.005f){
    coord = indice;
    Square::setColor(Color::WHITE);
}