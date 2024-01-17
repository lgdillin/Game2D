#include "Player.hpp"

Player::Player() {
	m_eyeHeightZone = HeightZone::EYELEVEL;
}

Player::~Player() {
}

void Player::move(float _x, float _y) {
	m_body->m_position.x = _x;
	m_body->m_position.y = _y;
}

void Player::turn() {
	
}

glm::vec3 Player::getPosition() {
	return m_body->m_position;
}

void Player::setBody(ShapeGeneric *_body) {
	m_body = _body;
}

ShapeGeneric *Player::getBody() {
	return m_body;
}
