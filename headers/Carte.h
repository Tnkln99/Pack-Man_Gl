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
    Player player = Player(indiceToCoordinate(659).first,indiceToCoordinate(659).second);
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

    const std::pair<float,float> indiceToCoordinate(int);
    const int coordinateToIndice(float,float);

    void update();

    void deleteCarte();
};