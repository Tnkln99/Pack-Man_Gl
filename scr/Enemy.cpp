#include "../headers/Enemy.h"

Enemy::Enemy(int indice, int type) : MoveableSquare(indice){
    switch(type){
        case 1:
            setColor(Color::ORANGE);
            type = 1;
        case 2:
            setColor(Color::RED);
            type = 2;
    }

}

bool Enemy::BFS(std::map<int,std::vector<int>> adj, int src, int dest, int v, int pred[], int dist[])
{
    // a queue to maintain queue of vertices whose
    // adjacency list is to be scanned as per normal
    // DFS algorithm
    std::list<int> queue;
 
    // boolean array visited[] which stores the
    // information whether ith vertex is reached
    // at least once in the Breadth first search
    bool visited[v];
 
    // initially all vertices are unvisited
    // so v[i] for all i is false
    // and as no path is yet constructed
    // dist[i] for all i set to infinity
    for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
 
    // now source is first to be visited and
    // distance from source to itself should be 0
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
 
    // standard BFS algorithm
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 
                // We stop BFS when we find
                // destination.
                if (adj[u][i] == dest)
                    return true;
            }
        }
    }
 
    return false;
}

int Enemy::nextMove(std::map<int,std::vector<int>> map, int playerPos){ //calculateur pour la prochaine tour
    // predecessor[i] array stores predecessor of
    // i and distance array stores distance of i
    // from s

    int v = 1600;
    int pred[v], dist[v];
    //std::cout << "bfs start" << std::endl;
    if (BFS(map, getCoord(), playerPos, v, pred, dist) == false) {
        std::cout << "Given source and playerPosition"
             << " are not connected";
        perror("BFS");
    }
 
    // vector path stores the shortest path
    std::vector<int> path;
    int crawl = playerPos;
    path.push_back(crawl);
    while (pred[crawl] != -1) {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }
    
    int res = path[path.size()-2];
    if (res - getCoord() == 1)
        setDirection(Directions::RIGHT);
    else if (res - getCoord() == -1)
        setDirection(Directions::LEFT);
    else if (res - getCoord() == 40)
        setDirection(Directions::DOWN);
    else if (res - getCoord() == -40)
        setDirection(Directions::UP);


    return res;
}

void Enemy::update(std::map<int,std::vector<int>> map, int playerPos){

    if(CanMove()){
        setCanMove(false);
        setTarget(nextMove(map, playerPos));
    }

    int target = getTarget();
    //std::cout << "enemy target is " << getTarget() << std::endl;
    
	glm::mat4 trans = glm:: mat4(1.0f);

    // Interpolation du déplacement
	if(getDirection() == Directions::UP){
		trans = glm::translate(trans, glm::vec3(0.0f, 0.0002f, 0.0f));
		setCenter(center.first,center.second + 0.0002f);
	}
	else if (getDirection() == Directions::LEFT){
		trans = glm::translate(trans, glm::vec3(-0.0002f, 0.0f, 0.0f));
		setCenter(center.first-0.0002f,center.second);
	}
	else if (getDirection() == Directions::DOWN){
		trans = glm::translate(trans, glm::vec3(0.0f, -0.0002f, 0.0f));
		setCenter(center.first,center.second-0.0002f);
	}
	else if (getDirection() == Directions::RIGHT){
		trans = glm::translate(trans, glm::vec3(0.0002f, 0.0f, 0.0f));
		setCenter(center.first+0.0002f,center.second);
	}
	else if (getDirection() == Directions::STOP)
		trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
	
	for(int i=0; i < 4; i ++){
		glm::vec4 tmp = trans * glm::vec4(getVertices()[i],1);
		setVertices(i, tmp.x, tmp.y, tmp.z);
	}

    // Mise à jour de l'indice
    std::pair<float, float> targetCenter = indiceToCoordinate(getTarget());
    double err = std::fabs(getCenter().first - targetCenter.first) + std::fabs(getCenter().second - targetCenter.second);
    //std::cout<< "err enemy : "<<err << std::endl;
    if(err < 0.0001){
        // setCoord(coordinateToIndice(getCenter().first,getCenter().second));
        setCoord(getTarget());
        setCenter(targetCenter.first, targetCenter.second);
        setCanMove(true);
        setDirection((Directions::STOP));
    }



	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW); 

    //delete vertTmp;
}
