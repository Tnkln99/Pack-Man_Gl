#include <stdio.h>
#include <iostream>
#include "Square.h"

class Player : public Square{
private:
    int health = 4;
    Keys direction;
    Keys savedDirection;
    int target; //indice de la case cible
    int coord; //indice of the player on the graph
public:
    Player(float,float);

    const Keys getDirection();
    const Keys getSavedDir();
    const int getTarget();
    const int getCoord();

    void setDirection(Keys);
    void setCoord(float,float);
    void setTarget(int);
    void setCoord(int);
    void setSavedDir(Keys);
    
    void update();
};