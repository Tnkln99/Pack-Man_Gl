#include "../headers/Player.h"

Player::Player(float centerx, float centery) : Square(centerx, centery, 0.05f){
	direction = Keys::UP;
    Square::setColor(Color::BLUE);
}

const Keys Player::getDirection(){
	return this->direction;
}

void Player::setDirection(Keys K){
	direction = K;
}

void Player::update(){
	drawSquare();
	glm::mat4 trans = glm:: mat4(1.0f);
    //std::cout<< MoveableSquare::getDirection() <<std::endl;
	if(getDirection() == Keys::UP)
        trans = glm::translate(trans, glm::vec3(0.0f, 0.0001f, 0.0f));	
	else if (getDirection() == Keys::LEFT)
		trans = glm::translate(trans, glm::vec3(-0.0001f, 0.0f, 0.0f));
	else if (getDirection() == Keys::DOWN)
		trans = glm::translate(trans, glm::vec3(0.0f, -0.0001f, 0.0f));
	else if (getDirection() == Keys::RIGHT)
		trans = glm::translate(trans, glm::vec3(0.0001f, 0.0f, 0.0f));
	
	for(int i=0; i < 4; i ++){
		glm::vec4 tmp = trans * glm::vec4(getVertices()[i],1);
		setVertices(i, tmp.x, tmp.y, tmp.z);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VAO);
    glm::vec3 vertTmp[4];

    for(int i = 0; i < 4; i ++){
        vertTmp[i] = getVertices()[i];
		//std::cout<<vertTmp[i].x<<" "<<vertTmp[i].y<<std::endl;
    }
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertTmp), vertTmp, GL_DYNAMIC_DRAW); 

    //delete vertTmp;
}