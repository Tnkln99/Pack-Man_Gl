#include <stdio.h>
#include <iostream>
#include "moveableSquare.h"

class Player : public MoveableSquare{
private:
    int health = 4;
public:
    Player(float , float, float, float, float, float, float, float);
    void update();
};