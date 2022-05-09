#include <stdio.h>
#include <iostream>
#include "MoveableSquare.h"
#include <map>
#include <vector>

class Player : public MoveableSquare{
private:
    int health = 4;
    bool Immunity = false;
public:
    Player(int indice, GLint shaderProgram);

    const int getHealth();
    const bool getImmunity();

    void setHealth(int);
    void setImmunity(bool);

    void update(std::map<int,std::vector<int>>);
};