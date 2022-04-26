#include "Player.h"
#include "Wall.h"
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <utility> 
#include <vector>


class Carte{
private:
    float points;
    Player player = Player(0.0f,0.0f);
    std::vector<Wall> walls;
    std::map <int,std::vector<int>> GrapMap;
public:
    Carte();

    const float getPoints();
    const Player getPlayer();
    const std::map<int,std::vector<int>> getGraphCarte();
    const std::vector<Wall> getWalls();
    const Keys getLastPressedKey();

    void setPlayerDirection(Keys direction);

    void loadMap();
    void drawMap();
    void drawSpace();

    const std::pair<float,float> indiceToCoordinate(int);

    void update();

    void deleteCarte();
};