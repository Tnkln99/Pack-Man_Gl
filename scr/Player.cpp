#include "../headers/Player.h"

Player::Player(float centerx, float centery) : Square(centerx, centery, 0.02f){
	direction = Keys::STOP;
    Square::setColor(Color::BLUE);
}

const Keys Player::getDirection(){
	return this->direction;
}

const Keys Player::getSavedDir(){
	return this->savedDirection;
}

const int Player::getTarget(){
	return this->target;
}

const int Player::getCoord(){
	return this->coord;
}

void Player::setDirection(Keys K){
	direction = K;
}

void Player::setTarget(int i){
	target = i;
}

void Player::setCoord(int i){
	coord = i;
}

void Player::setSavedDir(Keys k){
	this->savedDirection = k;
}


void Player::update(){
	glm::mat4 trans = glm:: mat4(1.0f);
    //std::cout<< MoveableSquare::getDirection() <<std::endl;
	if(getDirection() == Keys::UP){
		trans = glm::translate(trans, glm::vec3(0.0f, 0.0002f, 0.0f));
		setCenter(center.first,center.second + 0.0002f);
	}  	
	else if (getDirection() == Keys::LEFT){
		trans = glm::translate(trans, glm::vec3(-0.0002f, 0.0f, 0.0f));
		setCenter(center.first-0.0002f,center.second);
	}
	else if (getDirection() == Keys::DOWN){
		trans = glm::translate(trans, glm::vec3(0.0f, -0.0002f, 0.0f));
		setCenter(center.first,center.second-0.0002f);
	}
	else if (getDirection() == Keys::RIGHT){
		trans = glm::translate(trans, glm::vec3(0.0002f, 0.0f, 0.0f));
		setCenter(center.first+0.0002f,center.second);
	}	
	else if (getDirection() == Keys::STOP)
		trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
	
	for(int i=0; i < 4; i ++){
		glm::vec4 tmp = trans * glm::vec4(getVertices()[i],1);
		setVertices(i, tmp.x, tmp.y, tmp.z);
	}


	/*std::cout<<"center x : "<<center.first<<std::endl;
	std::cout<<"center y : "<<center.second<<std::endl;*/

	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW); 

    //delete vertTmp;
}