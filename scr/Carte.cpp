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
    for(int i = 0; i < walls.size(); i++){
        walls[i].drawSquare();
    }
}

void Carte::update(){
    drawMap();

    //std::cout << "can move : " << player.CanMove() << std::endl;
    if(this->player.CanMove()) {
        int playerIndice = this->getPlayerIndice();

        this->player.setCanMove(false);
        if (this->player.getDirection() == Keys::UP){
            this->player.setTarget(playerIndice - 40);
            std::cout<< "up" << std::endl;
        }
        else if (this->player.getDirection() == Keys::DOWN){
            this->player.setTarget(playerIndice + 40);
            std::cout<< "down" << std::endl;
        }
        else if (this->player.getDirection() == Keys::LEFT){
            this->player.setTarget(playerIndice - 1);
            std::cout<< "left" << std::endl;
        }
        else if (this->player.getDirection() == Keys::RIGHT){
            this->player.setTarget(playerIndice + 1);
            std::cout<< "right" << std::endl;
        }


        std::vector<int> moveableSpaces = GrapMap[playerIndice];

        int target = player.getTarget();
        /*if(std::find(moveableSpaces.begin(), moveableSpaces.end(), target) == moveableSpaces.end())
            for(int i : moveableSpaces)
                std::cout << "- Peut bouger en : " << i << std::endl;*/

        std::cout<< target << std::endl;
        int cpt = 0;
        for(int i = 0; i < moveableSpaces.size(); i ++){
            if(moveableSpaces[i]==target){
                break;
            }
            cpt++;
        }
        if(cpt == moveableSpaces.size())
            player.setDirection(Keys::STOP);
    }
    player.update();


}

void Carte::deleteCarte(){
    player.deleteVertexetBuff();
    for(int i = 0; i < walls.size(); i++){
        walls[i].deleteVertexetBuff();
    }
}