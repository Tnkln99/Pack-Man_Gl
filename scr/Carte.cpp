#include "../headers/Carte.h"


Carte::Carte(){
    std::cout<<player.getCenter().first<<" "<<player.getCenter().second<<std::endl;
    std::cout<<getPlayerIndice()<<std::endl;
    this->points = 0;
    for(int i = 0; i < 40; i++){
        for(int j = 0; j < 40; j++){
            indextoCord[i][j] = indiceToCoordinate(i * 40 + j);
            std::pair<int,int> i_j;
            i_j.first = i;
            i_j.second = j;
        }
    }
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
    for(int i = 0; i < 40; i++){
        for(int j = 0; j < 40; j++){
            if(player.getCenter().first == indextoCord[i][j].first && player.getCenter().second == indextoCord[i][j].second)
                this->player.setDirection(direction);
        }
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
                std::pair<float,float> x_y = indextoCord[i][j];
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
    int cptx = 0;
    while(x - 0.02f >= -1.0f){
        x -= 0.04f;
        cptx++;
    }
    int cpty = 0;
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

    /*bool isCollided = player.getCollided();

    for(int i = 0; i < walls.size();i++){
        glm::vec3 vertice3 = player.getVertices()[3];
        glm::vec3 vertice1 = player.getVertices()[1];
        std::pair<float,float> l1,r1;
        l1.first = vertice3.x;
        l1.second = vertice3.y;
        r1.first = vertice1.x;
        r1.second = vertice1.y;  
        if(walls[i].collide(l1,r1) && !isCollided){
            player.setCollided(true);
            player.setDirection(Keys::STOP);
            break;
        }          
    }*/


    player.update();
}

void Carte::deleteCarte(){
    player.deleteVertexetBuff();
    for(int i = 0; i < walls.size(); i++){
        walls[i].deleteVertexetBuff();
    }
}