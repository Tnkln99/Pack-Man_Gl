#include "../headers/Carte.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


Carte::Carte(){
    this->points = 0;
    player.setCoord(getPlayerIndice());
    this->loadMap();
}

const std::vector<Wall> Carte::getWalls(){
    return this->walls;
}

const Directions Carte::getLastPressedKey(){
    return this->player.getDirection();
}

const std::map<int,std::vector<int>> Carte::getGraphMap(){
    return this->GrapMap;
}

void Carte::setPlayerDirection(Directions direction){
    if(player.CanMove())
        player.setDirection(direction);
}

void Carte::loadMap(){
    std::string var;
    std::ifstream map;
    map.open("map.txt");
    if(!map){
        std::cerr << "Error: map can't be loaded!"<<std::endl;
        exit(1);
    }
    char tmpGraph[1640];//there are 1640 character in my map
    int ligne = 0;
    while( std::getline(map,var) ){
        for(int i = 0; i < var.size(); i++){
            tmpGraph[ligne*40+i] = var[i];
        }
        ligne++;
    }

    for(int i = 0; i < 40 ; i++){ //nombre de ligne de map
        for (int j = 0; j < 40; j++){ // nombre de cologne de map 
            if(tmpGraph[i * 40 + j] == ' '){
                GrapMap.insert({int (i * 40 + j), {}});
                if(tmpGraph[(i+1) * 40 + j] == ' ')
                    GrapMap[i * 40 + j].push_back((i+1) * 40 + j);
                if(tmpGraph[(i-1) * 40 + j] == ' ')
                    GrapMap[i * 40 + j].push_back((i-1) * 40 + j);
                if(tmpGraph[i * 40 + j+1] == ' ')
                    GrapMap[i * 40 + j].push_back(i * 40 + j+1);
                if(tmpGraph[i * 40 + j-1] == ' ')
                    GrapMap[i * 40 + j].push_back(i * 40 + j-1);
            }
            // initialisation des murs
            else if(tmpGraph[i * 40 + j] == 'B'){
                walls.push_back(Wall(i*40+j));
            }
            //else
                //std::cout<<"Z"; // printing it to be sure that it is correct
        }
    }
    drawMap();
}

const int Carte::getPlayerIndice(){
    return player.getCoord();
}

void Carte::drawMap(){
    player.drawSquare();
    for(auto & wall : walls){
        wall.drawSquare();
    }
}

void Carte::update(){
    drawMap();
    player.update(GrapMap);
}

void Carte::deleteCarte(){
    player.deleteVertexetBuff();
    for(int i = 0; i < walls.size(); i++){
        walls[i].deleteVertexetBuff();
    }
}