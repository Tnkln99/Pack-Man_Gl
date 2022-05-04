#include "../headers/MoveableSquare.h"

MoveableSquare::MoveableSquare(int indice) : Square(indiceToCoordinate(indice).first, indiceToCoordinate(indice).second, 0.02f){
	target = indice;
	coord = indice;
    Square::setColor(Color::BLUE);
}


const int MoveableSquare::getTarget(){
	return this->target;
}

const int MoveableSquare::getCoord(){
	return this->coord;
}

const Directions MoveableSquare::getDirection(){
	return this->direction;
}

void MoveableSquare::setDirection(Directions K){
	direction = K;
    if(K == Directions::STOP)
        setCanMove(true);
}

const bool MoveableSquare::CanMove() {
    return this->canMove;
}



void MoveableSquare::setCanMove(bool canMove) {
    this->canMove = canMove;
}

void MoveableSquare::setTarget(int i){
	target = i;
}

void MoveableSquare::setCoord(int i){
	coord = i;
}


void MoveableSquare::setCenter(float x, float y){
	Square::setCenter(x,y);
}