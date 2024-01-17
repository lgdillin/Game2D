#include "Rectangle.hpp"

Rectangle::Rectangle(glm::vec3 _pos, glm::vec3 _scale, bool _anc, float _angle,
	HeightZone _zone, std::string _texture
) : 
	ShapeGeneric(_pos, _scale, _anc, _angle, _zone
) {
	m_nVertices = 32;
	m_nIndices = 6;
	m_texture = _texture;

	recomputeBoundingVolume();
}

Rectangle::~Rectangle() {
}

void Rectangle::initialize() {
	//ShapeGeneric::initialize(m_nVertices, m_nIndices, m_vertices.data(), m_indices.data());
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// create the data store for the indices
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(unsigned int) * m_nIndices, m_indices.data(), GL_STATIC_DRAW);

	// create the data store for the vertices
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLfloat) * m_nVertices, m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(GLfloat), (GLvoid *)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	m_shaderId = Shader::buildShaderProgram("shader2.vert", "shader2.frag");


	buildTexture();
}

void Rectangle::buildTexture() {

	bool alphaMode = true;
	std::string fileLocation = "./resources/textures/" + m_texture + ".png";
	int width = 0;
	int height = 0;
	int bitDepth = 0;

	int stbiMode = alphaMode ? STBI_rgb_alpha : STBI_rgb;
	unsigned char *textureData = stbi_load(fileLocation.c_str(), &width,
		&height, &bitDepth, stbiMode);

	if (!textureData) {
		std::cout << "failed to load/find " << fileLocation
			<< " check location or mode " << std::endl;
	}

	// Generate a texture id and bind to the buffer
	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);

	// Handle texture wrapping on the S and T axis (read: X and Y axis)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Manage the scaling of the texture's look when very close/far
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLint glMode = alphaMode ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, glMode, width, height, 0,
		glMode, GL_UNSIGNED_BYTE, textureData);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(textureData);
}

void Rectangle::transform(glm::mat4 &_model) {
	_model = glm::translate(_model, m_position);
	_model = glm::rotate(_model, m_angleRad, m_rotAxis);
	_model = glm::scale(_model, m_scale);
}

void Rectangle::draw() {
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	Shader::setTexture(m_shaderId, "u_textureDiffuse", 0);
	glBindTexture(GL_TEXTURE_2D, m_textureId);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glDrawElements(GL_TRIANGLES, m_nIndices, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}

void Rectangle::recomputeBoundingVolume() {
	m_points = std::vector<glm::vec3>{
		glm::vec3(-1.0f, -1.0f, 0.0f),
		glm::vec3(1.0f, -1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(-1.0f, 1.0f, 0.0f)
	};
	for (int i = 0; i < m_points.size(); ++i) {
		m_points[i].x *= m_scale.x;
		m_points[i].y *= m_scale.y;

		float x = m_points[i].x * cos(m_angleRad)
			- m_points[i].y * sin(m_angleRad);
		float y = m_points[i].x * sin(m_angleRad)
			+ m_points[i].y * cos(m_angleRad);
		m_points[i].x = x;
		m_points[i].y = y;

		m_points[i].x += m_position.x;
		m_points[i].y += m_position.y;
	}

	m_normals = std::vector<glm::vec3>(4);
	for (int i = 0; i < 4; ++i) {
		glm::vec3 v = m_points[i] - m_points[(i + 1) % 4];
		float length = math2d::eucDist(v.x, v.y);
		float x = v.x / length;
		float y = v.y / length;
		m_normals[i] = glm::vec3(-y, x, 0.0);
	}
}

float Rectangle::signedDistanceFunction(glm::vec2 _p) {
	glm::vec2 v{ _p.x - m_position.x, _p.y - m_position.y };

	float x = v.x * cos(m_angleRad) - v.y * sin(m_angleRad);
	float y = -v.x * sin(-m_angleRad) + v.y * cos(m_angleRad);

	float qx = abs(x) - m_points[2].x;
	float qy = abs(y) - m_points[2].y;

	float dOutside = math2d::eucDist(glm::max(qx, 0.0f), glm::max(qy, 0.0f));
	float dInside = glm::max(glm::min(qx, 0.0f), glm::min(qy, 0.0f));
	return dOutside + dInside;
}
