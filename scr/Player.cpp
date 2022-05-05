#include "../headers/Player.h"

Player::Player(int indice) : MoveableSquare(indice){
    setDirection(Directions::STOP);
}

void Player::update(std::map<int,std::vector<int>> GrapMap){

    if(CanMove()) {

        int playerIndice = getCoord();

        setCanMove(false);
        if (getDirection() == Directions::UP){
            setTarget(playerIndice - 40);
            std::cout<< "up" << std::endl;
        }
        else if (getDirection() == Directions::DOWN){
            setTarget(playerIndice + 40);
            std::cout<< "down" << std::endl;
        }
        else if (getDirection() == Directions::LEFT){
            setTarget(playerIndice - 1);
            std::cout<< "left" << std::endl;
        }
        else if (getDirection() == Directions::RIGHT){
            setTarget(playerIndice + 1);
            std::cout<< "right" << std::endl;
        }

        //enemy algosu burda enemy.tageti bulucak enemy algosu bir graph alıcak ve ona göre işlemlerini yapıcak.

        int target = getTarget();
        std::vector<int> moveableSpaces = GrapMap[playerIndice];

        for(int i = 0; i < moveableSpaces.size(); i++){
            std::cout<< moveableSpaces[i]<< " ";
        }

        std::cout << std::endl;


        /*if(std::find(moveableSpaces.begin(), moveableSpaces.end(), target) == moveableSpaces.end())
            for(int i : moveableSpaces)
                std::cout << "- Peut bouger en : " << i << std::endl;*/

        int cpt = 0;
        for(int i = 0; i < moveableSpaces.size(); i ++){
            if(moveableSpaces[i]==target){
                break;
            }
            cpt++;
        }
        if(cpt == moveableSpaces.size())
            setDirection(Directions::STOP);
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