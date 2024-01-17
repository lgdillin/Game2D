#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/intersect.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GlfwGame.hpp"
#include "GlfwController.hpp"
#include "Triangle.hpp"

#include "Shader.hpp"

class GlfwView {
public:
	GlfwView(GlfwGame &_game, GlfwController &_controller);
	~GlfwView();

	void repaint();

	void paintRay();

	void recomputeVectors();

	glm::mat4 calculateViewMatrix();

	int initialize();

	static void keyHandlerCallback(
		GLFWwindow *_window,
		int _key,
		int _code,
		int _action,
		int _mode
	);

	static void mouseHandlerCallback(
		GLFWwindow *_window,
		double _xPos,
		double _yPos
	);

	static void mouseButtonCallback(
		GLFWwindow *_window,
		int _button,
		int _action,
		int _mods
	);

	bool getWindowShouldClose() { return glfwWindowShouldClose(m_window); }
	void swapBuffers() { glfwSwapBuffers(m_window); }

private:
	GlfwGame *m_game;
	GlfwController *m_controller;

	GLFWwindow *m_window;

	GLint m_windowWidth;
	GLint m_windowHeight;
	GLint m_bufferWidth;
	GLint m_bufferHeight;

	float m_fov;
	glm::mat4 m_projection;
	//glm::mat4 m_ortho;
};