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

const std::map<int,std::vector<int>> Carte::getGraphMap(){
    return this->GrapMap;
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
                std::pair<float,float> x_y = indiceToCoordinate(i * 40 + j);
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


const int Carte::coordinateToIndice(float x, float y){
    return 25 * (x + y) / (1.0f - (1.0f/40 * 40) - 1.0f/40);
}

const int Carte::getPlayerIndice(){
    return coordinateToIndice(this->player.getCenter().first,this->player.getCenter().second);
}

void Carte::drawMap(){
    player.drawSquare();
    for(int i = 0; i < walls.size(); i++){
        walls[i].drawSquare();
    }
}

void Carte::update(){
    drawMap();
    
    if (this->player.getDirection() == Keys::UP){
        this->player.setTarget(this->getPlayerIndice() - 40);
    }
    else if (this->player.getDirection() == Keys::DOWN){
        this->player.setTarget(this->getPlayerIndice() + 40);
    }
    else if (this->player.getDirection() == Keys::LEFT){
        this->player.setTarget(this->getPlayerIndice() - 1);
    }
    else if (this->player.getDirection() == Keys::RIGHT){
        this->player.setTarget(this->getPlayerIndice() + 1);
    }

    /*std::vector<int> moveableSpaces = GrapMap[getPlayerIndice()];

    for(int i = 0; i < moveableSpaces.size(); i++){
        std::cout<<moveableSpaces[i]<<" ";
    }*/


    int target = this->player.getTarget();

    /*if (std::find(moveableSpaces.begin(), moveableSpaces.end(), target) == moveableSpaces.end()){
        player.setDirection(Keys::STOP);
    }
    else{
        std::cout<<"cant move "<<std::endl;
    }*/
    
    //player.update();
}

void Carte::deleteCarte(){
    player.deleteVertexetBuff();
    for(int i = 0; i < walls.size(); i++){
        walls[i].deleteVertexetBuff();
    }
}