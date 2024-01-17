#pragma once

#include <iostream> 
#include <vector>
#include <array>

#include <GL/glew.h>

#include "stb_image.cpp"

#include "Shader.hpp"
#include "MyMath.hpp"
#include "MyEnums.hpp"

class ShapeGeneric {
public:
	ShapeGeneric(glm::vec3 _pos, glm::vec3 _scale, bool _anc, float _angle,
		HeightZone _zone);
	~ShapeGeneric();

	void initialize(int _nVertices, int _nIndices, GLfloat *_vertices, 
		unsigned int *_indices);
	virtual void initialize() {}
	virtual void buildTexture();

	virtual void transform(glm::mat4 &_model);
	virtual void draw();
	virtual void recomputeBoundingVolume() = 0;
	virtual float signedDistanceFunction(glm::vec2 _p);

	GLuint shader() { return m_shaderId; }
	void useShader() { glUseProgram(m_shaderId); }

	HeightZone m_heightZone;
	bool m_anchored;
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::vec3 m_rotAxis;
	float m_angleDeg;
	float m_angleRad;

	std::vector<glm::vec3> m_points;
	std::vector<glm::vec3> m_normals;

	GLuint m_textureId;
	std::string m_texture;
protected:
	int m_nVertices;
	int m_nIndices;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;
	GLuint m_shaderId;
};