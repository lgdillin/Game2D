#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include "Player.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "MyMath.hpp"
#include "Box.hpp"
#include "ShapeGeneric.hpp"
#include "WorldBuilder.hpp"
#include "Ray.hpp"

class GlfwGame {
public:
	GlfwGame();
	~GlfwGame();

	void initialize();

	void update();

	void separatingAxisTheorem2(ShapeGeneric *_a, ShapeGeneric *_b);

	float signedDistToScene(ShapeGeneric *_s, glm::vec2 _v);
	void calculateRaycaster();
	void turnPlayer();

	void setCursorPosition(GLfloat _mouseX, GLfloat _mouseY);
	void setWorldMousePos(float _x, float _y);

	void movePlayer(float _x, float _y);
	void moveCamera2D(float _x, float _y);

	void recomputeCameraVectors();

	glm::vec3 cameraPosition() { return m_cameraPosition; }
	void moveCamera(glm::vec3 _v) { m_cameraPosition = _v; }
	glm::vec3 cameraFront() { return m_front; }
	glm::vec3 cameraUp() { return m_up; }
	glm::vec3 cameraRight() { return m_right; }
	GLfloat yaw() { return m_yaw; }
	void setYaw(GLfloat _y) { m_yaw = _y; }
	GLfloat pitch() { return m_pitch; }
	void setPitch(GLfloat _p) { m_pitch = _p; }
	GLfloat roll() { return m_roll; }
	void setRoll(GLfloat _r) { m_roll = _r; }

	Ray m_ray;
	std::vector<ShapeGeneric *> m_shapes;
	Player m_player;
	GLfloat m_mouseX;
	GLfloat m_mouseY;
	float m_worldMouseX;
	float m_worldMouseY;
	glm::vec2 m_worldMouse;
	float m_maxLaserDist;
private:
	// physics variables
	//float m_gravity;

	glm::vec3 m_cameraPosition;
	GLfloat m_yaw; // left/right
	GLfloat m_pitch; // up/down
	GLfloat m_roll; // tilt
	glm::vec3 m_right;
	glm::vec3 m_front;
	glm::vec3 m_up; // Up relative to camera's rotation
};