#include "../headers/Player.h"

Player::Player(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) : MoveableSquare(x1,y1,x2,y2,x3,y3,x4,y4){
    MoveableSquare::setColor(Color::BLUE);
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
    }
	
	setCentre();

	/*for(int i=0; i < 2; i++){
		std::cout<<"centre x : "<<getCentre()[0]<<"centre y : "<<getCentre()[1]<<std::endl;
	}*/

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertTmp), vertTmp, GL_STREAM_DRAW); 

    //delete vertTmp;
}