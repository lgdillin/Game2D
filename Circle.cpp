#include "Circle.hpp"

Circle::Circle(glm::vec3 _pos, glm::vec3 _scale, bool _anc, float _angle, 
	HeightZone _zone, std::string _texture, float _radius
) : 
	ShapeGeneric(_pos, _scale, _anc, _angle, _zone
) {
	m_nVertices = 24;
	m_nIndices = 3;
	
	m_radius = _radius;

	recomputeBoundingVolume();
}

Circle::~Circle() {
}

void Circle::initialize() {
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
	
}

void Circle::buildTexture() {
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

void Circle::transform(glm::mat4 &_model) {
	_model = glm::translate(_model, m_position);
	_model = glm::rotate(_model, m_angleRad, m_rotAxis);
	_model = glm::scale(_model, m_scale);
}

void Circle::draw() {
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

void Circle::recomputeBoundingVolume() {
	m_scale.x = m_radius;
	m_scale.y = m_radius;

	m_points = std::vector<glm::vec3>{
		glm::vec3(0.0f, 0.0f, 0.0f), // central position
		glm::vec3(0.0f, 1.0f, 0.0f) // radius
	};

	m_points[0] = m_position;

	m_points[1] *= m_radius;
	m_points[1].x += m_position.x;
	m_points[1].y += m_position.y;
	

}
