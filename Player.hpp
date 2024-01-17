#pragma once

#include "ShapeGeneric.hpp"

class Player {
public:
	Player();
	~Player();

	void move(float _x, float _y);
	void turn();

	glm::vec3 getPosition();

	void setBody(ShapeGeneric *_body);
	ShapeGeneric *getBody();

	HeightZone m_eyeHeightZone;
private:
	ShapeGeneric *m_body;
};