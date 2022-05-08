#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Palette.h"
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <utility> 
#include <vector>
#include <algorithm>
#include <time.h>


class Carte{
private:
    float points;
    Player player = Player(659);
    Enemy enemy = Enemy(77,1);
    std::vector<Wall> walls;
    std::vector<Palette> palettes;
    std::map <int,std::vector<int>> GrapMap;

    time_t hitTime = 0;
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