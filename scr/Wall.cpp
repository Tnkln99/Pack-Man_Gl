#include "../headers/Wall.h"

Wall::Wall(float centerx, float centery) : Square(centerx, centery, 0.02f){
    Square::setColor(Color::PURPLE);
}