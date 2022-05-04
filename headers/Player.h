#include <stdio.h>
#include <iostream>
#include "MoveableSquare.h"
#include <map>
#include <vector>

class Player : public MoveableSquare{
private:
    int health = 4;
public:
    Player(int indice);

    const int getHealth();

    void setHealth(int);

    void update(std::map<int,std::vector<int>>);
};