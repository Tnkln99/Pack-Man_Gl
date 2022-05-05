#include "../headers/Enemy.h"

Enemy::Enemy(int indice, int type) : MoveableSquare(indice){
    switch(type){
        case 1:
            setColor(Color::ORANGE);
        case 2:
            setColor(Color::RED);
    }

}


int Enemy::nextMove(std::map<int,std::vector<int>> map, int playerPos){ //calculateur pour la prochaine tour
    return 561;
}

void Enemy::update(std::map<int,std::vector<int>> map, int playerPos){

    if(CanMove()) { 
        setCanMove(false);
        int target = nextMove(map, playerPos); 
    }

    int target = getTarget();
    //std::cout<< "target: "<<target << std::endl;
    //std::cout<< "coord: " <<getCoord() << std::endl;
    
	glm::mat4 trans = glm:: mat4(1.0f);

    //std::cout << "---- Center : " << center.first << " " << center.second <<std::endl;
    //std::cout << "---- Target : " << indiceToCoordinate(getTarget()).first << " " << indiceToCoordinate(getTarget()).second <<std::endl;

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
    // if(coordinateToIndice(getCenter().first,getCenter().second) != getCoord()){
    if(err < 0.0001){
        // setCoord(coordinateToIndice(getCenter().first,getCenter().second));
        setCoord(getTarget());
        setCenter(targetCenter.first, targetCenter.second);
        setCanMove(true);
        setDirection((Directions::STOP));
    }


	/*std::cout<<"center x : "<<center.first<<std::endl;
	std::cout<<"center y : "<<center.second<<std::endl;*/

	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW); 

    //delete vertTmp;
}
