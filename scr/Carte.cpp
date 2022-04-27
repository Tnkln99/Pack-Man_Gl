#include "../headers/Carte.h"


Carte::Carte(){
    this->points = 0;
    this->loadMap();
}

const std::vector<Wall> Carte::getWalls(){
    return this->walls;
}

const Keys Carte::getLastPressedKey(){
    return this->player.getDirection();
}

void Carte::setPlayerDirection(Keys direction){
    this->player.setDirection(direction);
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
        for (int j =0; j < 41; j++){ // nombre de cologne de map
            //std::cout<<tmpGraph[i * 40 + j]; 
            // initialisation de notre graph.
            if(tmpGraph[i * 40 + j] == ' '){
                std::cout<<" "; // printing it to be sure that it is correct
                GrapMap.insert(std::pair<int,std::vector<int>>(i,{}));
                if(tmpGraph[(i+1) * 40 + j] == ' ')
                    GrapMap[i].push_back((i+1) * 40 + j);
                if(tmpGraph[(i-1) * 40 + j] == ' ')
                    GrapMap[i].push_back((i-1) * 40 + j);
                if(tmpGraph[i * 40 + j+1] == ' ')
                    GrapMap[i].push_back(i * 40 + j+1);
                if(tmpGraph[i * 40 + j-1] == ' ')
                    GrapMap[i].push_back(i * 40 + j-1);
            }
            // initialisation des murs
            else if(tmpGraph[i * 40 + j] == 'B'){
                std::cout<<"B"; // printing it to be sure that it is correct
                std::pair<float,float> x_y = indiceToCoordinate(i * 40 + j);
                walls.push_back(Wall(x_y.first,x_y.second));
            }
            else
                std::cout<<"Z"; // printing it to be sure that it is correct
        }
        std::cout<<std::endl; // printing it to be sure that it is correct
    }

    /*for(int i = 0; i < walls.size(); i++){
        std::cout<<"Wall: "<<i<<" "<<walls[i].getCenter().first<<" "<<walls[i].getCenter().second<<std::endl;
    }*/

    drawMap();

    map.close();
}

const std::pair<float,float> Carte::indiceToCoordinate(int indice){
    float x = -1.0f + ((indice % 40) * 0.04f) + 0.02f;
    float y = 1.0f - ((indice / 40) * 0.04f) - 0.02f;
    return std::pair<float,float>(x,y);
}

const int Carte::coordinateToIndice(float x, float y){
    int indice = (int)((x + 1.0f) * 40.0f + (y - 1.0f) * 40.0f * 40.0f);
    return indice;
}

void Carte::drawMap(){
    player.drawSquare();
    for(int i = 0; i < walls.size(); i++){
        walls[i].drawSquare();
    }
}

void Carte::update(){
    drawMap();
    //player.update();
}

void Carte::deleteCarte(){
    player.deleteVertexetBuff();
    for(int i = 0; i < walls.size(); i++){
        walls[i].deleteVertexetBuff();
    }
}