#include "Player.h"
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <utility> 
#include <vector>

class Carte{
private:
    float points;
    Player player = Player(0.05f,  0.05f, 0.05f, -0.05f, -0.05f, -0.05f,-0.05f,  0.05f);
    std::map <int,std::vector<int>> GrapMap;
public:
    Carte();

    const float getPoints();
    const Player getPlayer();
    const std::map<int,int[]> getGraphCarte();

    void loadMap();
    void drawMap(const char[1640]);
    void drawWall();
    void update();

    void deleteCarte();
};