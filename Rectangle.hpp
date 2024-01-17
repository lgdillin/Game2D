#pragma once

#include <array>

#include "Shape2d.hpp"
#include "ShapeGeneric.hpp"

class Rectangle : public ShapeGeneric {
public:
	Rectangle(glm::vec3 _pos, glm::vec3 _scale, bool _anc, float _angle, 
		HeightZone _zone, std::string _texture);
	~Rectangle();

	void initialize() override;
	void buildTexture() override;
	void transform(glm::mat4 &_model) override;
	void draw() override;
	void recomputeBoundingVolume() override;
	float signedDistanceFunction(glm::vec2 _p) override;

private:

	std::array<GLfloat, 32> m_vertices = {
		// bottom left
		-1.0f, -1.0f, 0.0f, // position
		1.0f, 0.0f, 0.0f, // color
		0.0f, 0.0f,

		// bottom right
		1.0f, -1.0f, 0.0f, // position
		0.0f, 1.0f, 0.0f, // color
		1.0f, 0.0f,

		// top right
		1.0f, 1.0f, 0.0f, // pos
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f,

		// top left
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f
	};

	std::array<unsigned int, 6> m_indices = {
		0, 1, 2,
		2, 3, 0
	};

};