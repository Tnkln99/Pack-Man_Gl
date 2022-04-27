#include <stdio.h>
#include <iostream>
#include "Square.h"

class Player : public Square{
private:
    int health = 4;
    Keys direction;
    int target; //indice de la case cible
public:
    Player(float,float);

    const Keys getDirection();

    void setDirection(Keys);
    void setCoord(float,float);
    void setTarget(int);
    
    void update();
    void updateCenter();
};