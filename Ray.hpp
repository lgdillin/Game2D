#pragma once

#include <vector>

#include <GL/glew.h>

#include "Shader.hpp"

class Ray {
public:
	Ray();
	~Ray();

	void useShader() { glUseProgram(m_shaderId); }
	GLuint shader() { return m_shaderId; }
	void intialize();
	void setEndpoints(float _x1, float _y1, float _x2, float _y2);
	void transform(glm::mat4 &_model);
	void draw();


	void setOrigin(float _x, float _y);
	void setCutoff(float _x, float _y);
	void setDot(float _x, float _y);
	glm::vec2 getDot() { return glm::vec2(m_vertices[4], m_vertices[5]); }

	std::vector<GLfloat> m_vertices;
private:
	GLfloat m_originX;
	GLfloat m_originY;
	GLfloat m_cutoffX;
	GLfloat m_cutoffY;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_shaderId;
};