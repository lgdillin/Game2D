#include "Triangle.hpp"



Triangle::Triangle(glm::vec3 _pos, glm::vec3 _scale, bool _anc, float _angle,
	HeightZone _zone
) : 
	ShapeGeneric(_pos, _scale, _anc, _angle, _zone
) {
	m_nVertices = 18;
	m_nIndices = 3;
	recomputeBoundingVolume();
}

Triangle::~Triangle() {
}

void Triangle::initialize() {
	ShapeGeneric::initialize(m_nVertices, m_nIndices, m_vertices.data(), m_indices.data());
}

void Triangle::transform(glm::mat4 &_model) {
	_model = glm::translate(_model, m_position);
	_model = glm::rotate(_model, m_angleRad, m_rotAxis);
	_model = glm::scale(_model, m_scale);
}

void Triangle::draw() {

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glDrawElements(GL_TRIANGLES, m_nIndices, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


}

void Triangle::recomputeBoundingVolume() {
	m_points = std::vector<glm::vec3>{
	glm::vec3(-1.0f, -1.0f, 0.0f),
	glm::vec3(1.0f, -1.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f)
	};
	for (int i = 0; i < m_points.size(); ++i) {
		m_points[i].x *= m_scale.x;
		m_points[i].y *= m_scale.y;

		m_points[i].x += m_position.x;
		m_points[i].y += m_position.y;
	}

	m_normals = std::vector<glm::vec3>(3);
	for (int i = 0; i < m_points.size(); ++i) {
		glm::vec3 v = m_points[i] - m_points[(i + 1) % m_points.size()];
		float length = glm::sqrt(v.x * v.x + v.y * v.y);
		float x = v.x / length;
		float y = v.y / length;
		m_normals[i] = glm::vec3(-y, x, 0.0);
	}
}
