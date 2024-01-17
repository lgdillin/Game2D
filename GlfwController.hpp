#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "GlfwGame.hpp"

class GlfwController {
public:
	GlfwController(GlfwGame &_game);
	~GlfwController();

	void keyControl(GLfloat _deltaTime);
	void mouseControl();
	void mouseClickControl();

	void setKey(int _key, bool _state);

	/// getters and setters
	bool firstMouseMovement() { return m_firstMouseMovement; }
	void firstMouseMovement(bool _m) { m_firstMouseMovement = _m; }

	GLfloat lastMouseX() { return m_lastMouseX; }
	void lastMouseX(GLfloat _x) { m_lastMouseX = _x; }

	GLfloat lastMouseY() { return m_lastMouseY; }
	void lastMouseY(GLfloat _y) { m_lastMouseY = _y; }

	GLfloat mouseDeltaX() { return m_mouseDeltaX; }
	void mouseDeltaX(GLfloat _x) { m_mouseDeltaX = _x; }

	GLfloat mouseDeltaY() { return m_mouseDeltaY; }
	void mouseDeltaY(GLfloat _y) { m_mouseDeltaY = _y; }

	bool m_mButtonLeft;
	bool m_mButtonRight;
	GLfloat m_mouseX;
	GLfloat m_mouseY;
private:
	GlfwGame *m_game;

	bool m_keys[1024];
	bool m_keyHit[1024];

	bool m_firstMouseMovement;
	GLfloat m_lastMouseX;
	GLfloat m_lastMouseY;
	GLfloat m_mouseDeltaX;
	GLfloat m_mouseDeltaY;
};