#pragma once

#include "ShapeGeneric.hpp"

class Circle : public ShapeGeneric {
public:
	Circle(glm::vec3 _pos, glm::vec3 _scale, bool _anc, float _angle,
		HeightZone _zone, std::string _texture, float _radius);
	~Circle();

	void initialize() override;
	void buildTexture() override;
	void transform(glm::mat4 &_model) override;
	void draw() override;
	void recomputeBoundingVolume() override;

	float m_radius;
private:

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;

	std::array<GLfloat, 24> m_vertices{
		-1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,

		0.5f, 2.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		0.5f, 1.0f
	};
	
	std::array<unsigned int, 3> m_indices{
		0, 1, 2
	};
};