#pragma once

#include <iostream>
#include <array>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShapeGeneric.hpp"
#include "Shader.hpp"

class Triangle : public ShapeGeneric {
public:
	Triangle(glm::vec3 _pos, glm::vec3 _scale, bool _anc, float _angle,
		HeightZone _zone);
	~Triangle();

	void initialize() override;
	void transform(glm::mat4 &_model) override;
	void draw();

	void recomputeBoundingVolume() override;

private:

	std::array<GLfloat, 18> m_vertices = {
		// bottom left
		-1.0f, -1.0f, 0.0f, // position
		1.0f, 0.0f, 0.0f, // color

		// bottom right
		1.0f, -1.0f, 0.0f, // position
		0.0f, 1.0f, 0.0f, // color

		// top center
		0.0f, 1.0f, 0.0f, // pos
		0.0f, 0.0f, 1.0f
	};

	std::array<unsigned int, 3> m_indices = {
		0, 1, 2
	};
};