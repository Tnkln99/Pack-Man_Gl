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
    Player player = Player(899,0);
    Enemy enemy = Enemy(659,2,0);
    std::vector<Wall> walls;
    std::vector<Palette> palettes;
    std::map <int,std::vector<int>> GrapMap;

    time_t hitTime = 0;
public:
    Carte(GLint shaderProgram);

    const float getPoints();
    const Player getPlayer();
    const std::map<int,std::vector<int>> getGraphMap();
    const std::vector<Wall> getWalls();
    const Directions getLastPressedKey();
    const int getPlayerIndice();


    void setPlayerDirection(Directions direction);


    void loadMap(GLint shaderProgram);
    void drawMap();

    void update();

    void deleteCarte();
};