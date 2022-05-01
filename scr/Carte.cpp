#include "../headers/Carte.h"


Carte::Carte(){
    this->points = 0;
    player.setCoord(getPlayerIndice());
    std::cout<<player.getCoord()<<std::endl;
    this->loadMap();
}

const std::vector<Wall> Carte::getWalls(){
    return this->walls;
}

const Keys Carte::getLastPressedKey(){
    return this->player.getDirection();
}

const std::map<int,std::vector<int>> Carte::getGraphMap(){
    return this->GrapMap;
}

void Carte::setPlayerDirection(Keys direction){
    
    if ( indiceToCoordinate(player.getCoord()).first != player.getCenter().first && indiceToCoordinate(player.getCoord()).second != player.getCenter().second){
        player.setSavedDir(direction);
    }
    else if (player.getSavedDir() != Keys::NONE){
        this->player.setDirection(player.getSavedDir());
        player.setSavedDir(Keys::NONE);
    }
    else{
        player.setDirection(direction);
    }
        
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
                std::pair<float,float> x_y = indiceToCoordinate(i*40+j);
                walls.push_back(Wall(x_y.first,x_y.second));
            }
            //else
                //std::cout<<"Z"; // printing it to be sure that it is correct
        }
    }
    drawMap();
}

const std::pair<float,float> Carte::indiceToCoordinate(int indice){
    float x = -1.0f + ((indice % 40) * 0.04f) + 0.02f;
    float y = 1.0f - ((indice / 40) * 0.04f) - 0.02f;
    return std::pair<float,float>(x,y);
}

const int Carte::coordinateToIndice(float x,float y){
    int cptx = 0; // j
    while(x - 0.02f >= -1.0f){
        x -= 0.04f;
        cptx++;
    }
    int cpty = 0; // i
    while(y + 0.02f<= 1.0f){
        y += 0.04f;
        cpty++;
    }
    //std::cout<<"cptx: "<<cptx<<" cpty: "<<cpty<<std::endl;
    return cpty * 40 + cptx;
}

const int Carte::getPlayerIndice(){
    return coordinateToIndice(player.getCenter().first,player.getCenter().second);
}

void Carte::drawMap(){
    player.drawSquare();
    for(int i = 0; i < walls.size(); i++){
        walls[i].drawSquare();
    }
}

void Carte::update(){
    drawMap();

    int playerIndice = this->getPlayerIndice();

    if (this->player.getDirection() == Keys::UP){
        this->player.setTarget(playerIndice - 40);
    }
    else if (this->player.getDirection() == Keys::DOWN){
        this->player.setTarget(playerIndice + 40);
    }
    else if (this->player.getDirection() == Keys::LEFT){
        this->player.setTarget(playerIndice - 1);
    }
    else if (this->player.getDirection() == Keys::RIGHT){
        this->player.setTarget(playerIndice + 1);
    }

    if(coordinateToIndice(player.getCenter().first,player.getCenter().second)!=player.getCoord()){
        player.setCoord(coordinateToIndice(player.getCenter().first,player.getCenter().second));
    }

    std::vector<int> moveableSpaces = GrapMap[getPlayerIndice()];

    int target = player.getTarget();
    int cpt = 0;
    for(int i = 0; i < moveableSpaces.size(); i ++){
        if(moveableSpaces[i]==target){
            break;
        }
        cpt++;
    }

    if(cpt == moveableSpaces.size())
        player.setDirection(Keys::STOP);

    std::cout<< indiceToCoordinate(player.getCoord()).first << " ";
    std::cout<< player.getCenter().first<<std::endl;

    std::cout<< indiceToCoordinate(player.getCoord()).second << " ";
    std::cout<< player.getCenter().second<<std::endl;


    player.update();
}

void Carte::deleteCarte(){
    player.deleteVertexetBuff();
    for(int i = 0; i < walls.size(); i++){
        walls[i].deleteVertexetBuff();
    }
}