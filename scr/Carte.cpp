#include "../headers/Carte.h"


Carte::Carte(){
    this->points = 0;
    this->loadMap();
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

    // initialisation de notre graph.
    for(int i = 0; i < 40; i++){ 
        for (int j =0; j < 41; j++){
            std::cout<<tmpGraph[i * 40 + j];
            if(tmpGraph[i * 40 + j] == ' '){
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
        }
        std::cout<<std::endl;
    }

    drawMap(tmpGraph);

    map.close();
}

void Carte::drawMap(const char tmpGraph[1640]){
    
}

void Carte::deleteCarte(){
    player.deleteVertexetBuff();
}