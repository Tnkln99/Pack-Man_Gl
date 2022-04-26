#include <stdio.h>
#include <iostream>
#include "Square.h"

class Player : public Square{
private:
    int health = 4;
    Keys direction;
public:
    Player(float,float);

    const Keys getDirection();

    void setDirection(Keys);
    
    void update();
};