#pragma once

#include <iostream>
#include <vector>
#include <array>

#include <GL/glew.h>

#include "Shader.hpp"
#include "MyMath.hpp"
#include "MyEnums.hpp"
#include "ShapeGeneric.hpp"

class Shape2d : public ShapeGeneric {
public:
	Shape2d(glm::vec3 _pos, glm::vec3 _scale, bool _anc, float _angle, 
		HeightZone _zone);
	~Shape2d();

	//void initialize(int _nVertices, int _nIndices,GLfloat *_vertices, unsigned int *_indices);

	//virtual void initialize() {}

	//virtual void transform(glm::mat4 &_model);
	//virtual void draw();
	//virtual void recomputeBoundingVolume() = 0;

protected:

private:
};