#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <utility> 
#include <vector>
#include <algorithm>


class Carte{
private:
    float points;
    Player player = Player(659);
    Enemy enemy = Enemy(77,1);
    std::vector<Wall> walls;
    std::map <int,std::vector<int>> GrapMap;  
public:
    Carte();

    const float getPoints();
    const Player getPlayer();
    const std::map<int,std::vector<int>> getGraphMap();
    const std::vector<Wall> getWalls();
    const Directions getLastPressedKey();
    const int getPlayerIndice();

    void setPlayerDirection(Directions direction);

    void loadMap();
    void drawMap();

    void update();

    void deleteCarte();
};