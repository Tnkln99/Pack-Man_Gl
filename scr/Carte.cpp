#include "../headers/Carte.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


Carte::Carte(GLint shaderProgram){
    player = Player(899,shaderProgram);
    enemy = Enemy(659,2,shaderProgram);
    this->points = 0;
    this->loadMap(shaderProgram);
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

void Carte::loadMap(GLint shaderProgram){
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
    int cpt = 0;
    for(int i = 0; i < 40 ; i++){ //nombre de ligne de map
        for (int j = 0; j < 40; j++){ // nombre de cologne de map 
            if(tmpGraph[i * 40 + j] == ' '){
                GrapMap.insert({int (i * 40 + j), {}});
                palettes.push_back(Palette(i * 40 + j,shaderProgram));
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
                walls.push_back(Wall(i*40+j, shaderProgram));
            }
        }
    }
    drawMap();
}

void Carte::drawMap(){
    enemy.drawSquare();
    player.drawSquare();
    for(auto & wall : walls){
        wall.drawSquare();
    }
    for (auto & palette : palettes){
        palette.drawSquare();
    }
}

void Carte::update(){
    drawMap();
    //std:: cout << "immunity of player " << (bool)player.getImmunity() << std::endl;
    if(player.getHealth() <= 0){
        std::cout << "You lose!" << std::endl;
        exit(0);
    }
    //std::cout<<"player health: "<<player.getHealth()<<std::endl;

    time_t realTime;
    realTime = time(NULL);
    if(realTime - hitTime > 1.0f){
        player.setImmunity(false);
    }
    else{
        player.setImmunity(true);
    }

    if(player.getImmunity()){
        enemy.update(GrapMap,77);
    }
    else{
        //double err = std::fabs(player.getCenter().first - enemy.getCenter().first) + std::fabs(player.getCenter().second - enemy.getCenter().second);
        if(player.getCoord() == enemy.getCoord()){ 
            //std::cout<<"get hit by enemy"<<std::endl;
            player.setHealth(player.getHealth()-1);
            hitTime = realTime;
            player.setImmunity(true);
            enemy.update(GrapMap,77);
        }
        enemy.update(GrapMap,player.getCoord());
    }

    for(auto it = std::begin(palettes); it != std::end(palettes); ++it) {
        if(it->getCoord() == player.getCoord()){
            palettes.erase(it);
            points++;
            //it->deleteVertexetBuff();
        }
    }

    //std::cout << "your points is " << points << std::endl;
        
    player.update(GrapMap);
}

void Carte::deleteCarte(){
    player.deleteVertexetBuff();
    for(int i = 0; i < walls.size(); i++){
        walls[i].deleteVertexetBuff();
    }
    for (auto & palette : palettes){
        palette.deleteVertexetBuff();
    }
    enemy.deleteVertexetBuff();
}