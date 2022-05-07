#include <stdio.h>
#include <iostream>
#include "MoveableSquare.h"
#include <map>
#include <vector>
#include <bits/stdc++.h>

class Enemy : public MoveableSquare{
private:
    int type;
public:
    Enemy(int indice, int type);
    
    bool BFS(std::map<int,std::vector<int>>,int,int,int,int*,int*);
    int nextMove(std::map<int,std::vector<int>> map, int playerPos);

    void update(std::map<int,std::vector<int>> map, int playerPos);
};