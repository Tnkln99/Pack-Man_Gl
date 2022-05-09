#pragma once 
#include <stdio.h>
#include <iostream>
#include "Square.h"

class MoveableSquare : public Square{
private:
    int health = 4;
    int target; //indice de la case cible
    int coord; //indice of the square on the graph
    bool canMove = true;
    Directions direction;
public:
    MoveableSquare(int indice, GLint shaderProgram);

    const int getTarget();
    const int getCoord();
    const bool CanMove();
    const Directions getDirection();

    void setDirection(Directions);
    void setCanMove(bool canMove);
    void setCoord(float,float);
    void setTarget(int);
    void setCoord(int);
    void setCenter(float,float) override;
};