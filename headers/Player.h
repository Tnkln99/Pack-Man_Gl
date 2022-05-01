#include <stdio.h>
#include <iostream>
#include "Square.h"

class Player : public Square{
private:
    int health = 4;
    Keys direction;
    int target; //indice de la case cible
    int coord; //indice of the player on the graph
    bool collided;
public:
    Player(float,float);

    const Keys getDirection();
    const int getTarget();
    const int getCoord();
    const bool getCollided();

    void setDirection(Keys);
    void setCoord(float,float);
    void setTarget(int);
    void setCoord(int);
    void setCollided(bool);
    
    void update();
    void updateCenter();
};