#include "Ray.hpp"

Ray::Ray() {
	m_originX = 0.0f;
	m_originY = 0.0f;
	m_cutoffX = 1.0f;
	m_cutoffY = 1.0f;


	m_vao = 0;
	m_vbo = 0;
	m_shaderId = 0;

	m_vertices = std::vector<GLfloat>{
		m_originX, m_originY, m_cutoffX, m_cutoffY, m_cutoffX, m_cutoffY
	};
}

Ray::~Ray() {
}

void Ray::intialize() {
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4, m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	m_shaderId = Shader::buildShaderProgram("shader_line.vert", "shader_line.frag");
}

void Ray::setEndpoints(float _x1, float _y1, float _x2, float _y2) {
	m_vertices[0] = _x1;
	m_vertices[1] = _y1;
	m_vertices[2] = _x2;
	m_vertices[3] = _y2;

}

void Ray::transform(glm::mat4 &_model) {
	_model = glm::translate(_model, glm::vec3(m_vertices[0], m_vertices[1], 0.0f));
	_model = glm::translate(_model, glm::vec3(m_vertices[2], m_vertices[3], 0.0f));
}

void Ray::draw() {
	glUseProgram(m_shaderId);

	glBindVertexArray(m_vao);
	glDrawArrays(GL_LINES, 0, 2);

	glPointSize(10.0f);
	glDrawArrays(GL_POINTS, 2, 1);
	glBindVertexArray(0);
}

void Ray::setOrigin(float _x, float _y) {
	m_originX = _x;
	m_originY = _y;
	m_vertices[0] = _x;
	m_vertices[1] = _y;
}

void Ray::setCutoff(float _x, float _y) {
	m_cutoffX = _x;
	m_cutoffY = _y;
	m_vertices[2] = _x;
	m_vertices[3] = _y;
}

void Ray::setDot(float _x, float _y) {
	m_vertices[4] = _x;
	m_vertices[5] = _y;
}
