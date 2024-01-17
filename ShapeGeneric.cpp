#include "ShapeGeneric.hpp"

ShapeGeneric::ShapeGeneric(glm::vec3 _pos, glm::vec3 _scale, bool _anc, 
	float _angle, HeightZone _zone
) {
	m_heightZone = _zone;
	m_anchored = _anc;
	m_position = _pos;
	m_scale = _scale;
	m_angleDeg = _angle;
	m_angleRad = glm::radians(_angle);
	m_nVertices = 0;
	m_nIndices = 0;
	m_vao = 0;
	m_vbo = 0;
	m_ibo = 0;
	m_shaderId = 0;

	m_rotAxis = glm::vec3(0.0f, 0.0f, 1.0f);
}

ShapeGeneric::~ShapeGeneric() {
}


void ShapeGeneric::initialize(int _nVertices, int _nIndices, GLfloat *_vertices, 
	unsigned int *_indices
) {
	/// Initialize Render portion
	m_nVertices = _nVertices;
	m_nIndices = _nIndices;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// create the data store for the indices
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(unsigned int) * _nIndices, _indices, GL_STATIC_DRAW);

	// create the data store for the vertices
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLfloat) * _nVertices, _vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(GLfloat), (GLvoid *)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	m_shaderId = Shader::buildShaderProgram("shader1.vert", "shader1.frag");
}

void ShapeGeneric::buildTexture() {

}

void ShapeGeneric::transform(glm::mat4 &_model) {
}

void ShapeGeneric::draw() {
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glDrawElements(GL_TRIANGLES, m_nIndices, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

float ShapeGeneric::signedDistanceFunction(glm::vec2 _p) {
	return 0.0f;
}
