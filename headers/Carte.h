#include "Player.h"
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
    std::vector<Wall> walls;
    std::map <int,std::vector<int>> GrapMap;  
public:
    Carte();

    const float getPoints();
    const Player getPlayer();
    const std::map<int,std::vector<int>> getGraphMap();
    const std::vector<Wall> getWalls();
    const Keys getLastPressedKey();
    const int getPlayerIndice();

    void setPlayerDirection(Keys direction);

    void loadMap();
    void drawMap();

    void update();

    void deleteCarte();
};