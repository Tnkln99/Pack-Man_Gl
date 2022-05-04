#include "../headers/Enemy.h"

Enemy::Enemy(int indice, int type) : MoveableSquare(indice){
    switch(type){
        case 1:
            setColor(Color::ORANGE);
        case 2:
            setColor(Color::RED);
    }

}

int Enemy::nextMove(std::map<int,std::vector<int>> map, int playerPos){ //calculateur pour la prochaine tour
    return 561;
}

void Enemy::update(std::map<int,std::vector<int>> map, int playerPos){
    if(CanMove()) {
        setTarget(nextMove(map, playerPos));
    }
}