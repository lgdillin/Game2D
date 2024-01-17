#pragma once

#include <iostream>
#include <array>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "ShapeGeneric.hpp"
#include "Shader.hpp"
#include "MyEnums.hpp"
#include "MyMath.hpp"
#include "stb_image.cpp"

class Box : public ShapeGeneric {
public:
	Box(glm::vec3 _pos, glm::vec3 _scale, bool _anc, float _angle, HeightZone _zone);
	~Box();

	void initialize() override;
	void buildTexture() override;

	void transform(glm::mat4 &_model) override;
	void draw() override;
	void recomputeBoundingVolume() override;


private:
	//GLuint m_textureId;

	std::array<unsigned int, 36> m_indices = {
		0, 1, 2, // front left triangle
		2, 3, 0, // front right triangle

		5, 4, 7, // back left triangle
		7, 6, 5, // back right triangle

		12, 13, 14, // bottom left triangle
		14, 15, 12, // bottom right triangle

		16, 17, 18, // right left triangle
		18, 19, 16, // right right triangle

		20, 21, 22, // top left triangle
		22, 23, 20, // top right triangle

		8, 9, 10, // left left triangle
		10, 11, 8, // left right triangle
	};

	std::array<GLfloat, 192> m_vertices = {
		// Front face
		// 0F: front bottom left
		-1.0f, -1.0f, 1.0f, // x, y, z
		1.0f, 0.0f, 0.0f, // r, g, b
		0.0f, 0.0f, // s,t

		// 1F: Bottom Front Right
		1.0f, -1.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f,

		// 2F: Front Top Right
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f,

		// 3F: Front Top Left
		-1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,

		// Back Face
		// 4B: Back Bottom Left
		-1.0f, -1.0f, -1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f,

		// 5B: Back Bottom Right 
		1.0f, -1.0f, -1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f,

		// 6B: Back Top Right 
		1.0f, 1.0f, -1.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f,

		// 7B: Back Top Left
		-1.0f, 1.0f, -1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f,

		// Left face
		// 8L: Left Bottom Left
		-1.0f, -1.0f, -1.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 0.0f,

		// 9L: Right Bottom Right
		-1.0f, -1.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f,

		// 10L: Left Top Right
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f,

		// 11L: Left Top Left
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f,

		// Under Face
		// 12U: Under Bottom Left
		-1.0f, -1.0f, -1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f,

		// 13U: Under Bottom Right
		1.0f, -1.0f, -1.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f,

		// 14U: Under Top Right
		1.0f, -1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f,

		// 15U: Under Top Left
		-1.0f, -1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f,

		// Right Face
		// 16R: Right Bottom Left
		1.0f, -1.0f, 1.0f,
		1.0f, 0.0f, 0.2f,
		0.0f, 0.0f,

		// 17R: Right Bottom Right
		1.0f, -1.0f, -1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,

		// 18R: Right Top Right
		1.0f, 1.0f, -1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f,

		// 19R: Right Top Left
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f,

		// Top Face
		// 20T: Top Bottom Left
		-1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 0.0f,

		// 21T: Top Bottom Right
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f,

		// 22T: Top Top Right
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f,

		// 23T: Top Top Left
		-1.0f, 1.0f, -1.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f,
	};
};