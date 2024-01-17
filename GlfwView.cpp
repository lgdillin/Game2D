#include "GlfwView.hpp"

GlfwView::GlfwView(GlfwGame &_game, GlfwController &_controller) {
	m_controller = &_controller;
	m_game = &_game;

	m_windowWidth = 1000;
	m_windowHeight = 1000;
	m_bufferWidth = 0;
	m_bufferHeight = 0;

	m_window = nullptr;

	m_fov = 90.0f;
	m_projection = glm::mat4(1);
	//m_ortho = glm::ortho(0.0f, (float)m_windowWidth, 0.0f, (float)m_windowHeight, 0.1f, 100.0f);
}

GlfwView::~GlfwView() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void GlfwView::repaint() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	paintRay();

	glm::mat4 model(1);
	for (auto& s : m_game->m_shapes) {
		s->useShader();
		GLuint shader = s->shader();
		Shader::setMat4(shader, "u_projection", m_projection);
		Shader::setMat4(shader, "u_view", calculateViewMatrix());
		Shader::setXY(shader, "u_resolution", glm::vec2(m_bufferWidth, m_bufferHeight));

		s->transform(model);
		Shader::setMat4(shader, "u_model", model);
		
		s->draw();
		model = glm::mat4(1);
	}

}

void GlfwView::paintRay() {
	glm::mat4 view = calculateViewMatrix();
	float ndcX = (2.0f * m_controller->lastMouseX()) / m_windowWidth - 1.0f;
	float ndcY = 1.0f - (2.0f * m_controller->lastMouseY()) / m_windowHeight;

	glm::vec4 objViewSpace = view * glm::vec4(m_game->m_player.getBody()->m_position, 1.0f);
	float focalLength = 1.0f / tanf(glm::radians(m_fov / 2.0f));
	float ar = (float)m_windowHeight / (float)m_windowWidth;
	glm::vec3 ray_view = glm::vec3(ndcX / focalLength, (ndcY) / focalLength, 1.0f);
	glm::vec4 ray_intersect = glm::vec4(ray_view * -objViewSpace.z, 1.0f);
	glm::vec4 v = glm::inverse(view) * ray_intersect;

	glm::vec3 playerPos = glm::vec3(m_game->m_player.getBody()->m_position.x, m_game->m_player.getBody()->m_position.y, 1.0f);

	m_game->m_ray.useShader();
	GLuint shader = m_game->m_ray.shader();
	m_game->m_ray.setOrigin(m_game->m_player.getBody()->m_position.x, m_game->m_player.getBody()->m_position.y);
	m_game->m_ray.setCutoff(v.x, v.y);
	Shader::setMat4(shader, "u_projection", m_projection);
	Shader::setMat4(shader, "u_view", calculateViewMatrix());
	Shader::setXY(shader, "u_origin", glm::vec2(m_game->m_player.getBody()->m_position.x,
		m_game->m_player.getBody()->m_position.y));
	Shader::setXY(shader, "u_end", glm::vec2(v.x, v.y));
	Shader::setXY(shader, "u_dot", m_game->m_ray.getDot());
	m_game->setWorldMousePos(v.x, v.y);
	m_game->m_ray.draw();
}

glm::mat4 GlfwView::calculateViewMatrix() {
	return glm::lookAt(m_game->cameraPosition(),
		m_game->cameraPosition() + m_game->cameraFront(), m_game->cameraUp());
}

int GlfwView::initialize() {
	if (!glfwInit()) {
		std::cout << "Failed to init GLFW\n";
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// glew experimental?

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "GLFW View",
		nullptr, nullptr);

	GLenum error = glGetError();
	if (!m_window) {
		std::cout << "GLFW window failed error: " << error << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwGetFramebufferSize(m_window, &m_bufferWidth, &m_bufferHeight);

	glfwSetKeyCallback(m_window, keyHandlerCallback);
	glfwSetCursorPosCallback(m_window, mouseHandlerCallback);
	glfwSetMouseButtonCallback(m_window, mouseButtonCallback);

	glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GLFW_TRUE);
	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(m_window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "glewInit() failed\n";
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, m_bufferWidth, m_bufferHeight);

	glfwSetWindowUserPointer(m_window, this);

	//m_projection = glm::ortho(
	//	0.0f, 
	//	1.0f,
	//	0.0f, 
	//	1.0f,
	//	0.1f, 
	//	100.0f);

	// may need to change to an orthographic
	m_projection = glm::perspective(glm::radians(m_fov),
		(GLfloat)(m_bufferWidth / m_bufferHeight), 0.1f, 100.0f);

}

void GlfwView::keyHandlerCallback(GLFWwindow *_window, int _key, int _code, int _action, int _mode
) {
	GlfwView *view = static_cast<GlfwView *>(glfwGetWindowUserPointer(_window));

	if (_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS) {
		glfwSetWindowShouldClose(_window, GL_TRUE);
	}

	if (_key >= 0 && _key < 1024) {
		if (_action == GLFW_PRESS) {
			view->m_controller->setKey(_key, true);
		} else if (_action == GLFW_RELEASE) {
			view->m_controller->setKey(_key, false);
		}
	}
}

void GlfwView::mouseHandlerCallback(GLFWwindow *_window, double _xPos, double _yPos) {
	GlfwView *view = static_cast<GlfwView *>(glfwGetWindowUserPointer(_window));

	
	
	if (view->m_controller->firstMouseMovement()) {
		view->m_controller->lastMouseX(_xPos);
		view->m_controller->lastMouseY(_yPos);
		view->m_controller->firstMouseMovement(false);
	}

	view->m_controller->mouseDeltaX(_xPos - view->m_controller->lastMouseX());
	view->m_controller->mouseDeltaY(view->m_controller->lastMouseY() - _yPos);

	view->m_controller->lastMouseX(_xPos);
	view->m_controller->lastMouseY(_yPos);
}

void GlfwView::mouseButtonCallback(GLFWwindow *_window, int _button, int _action, int _mods) {
	GlfwView *view = static_cast<GlfwView *>(glfwGetWindowUserPointer(_window));

	double xpos, ypos;
	glfwGetCursorPos(view->m_window, &xpos, &ypos);
	view->m_controller->m_mouseX = xpos;
	view->m_controller->m_mouseY = ypos;

	if (_button == GLFW_MOUSE_BUTTON_LEFT && _action == GLFW_PRESS) {
		// Handle left mouse button click at position (xpos, ypos)
		view->m_controller->m_mButtonLeft = true;
	} else if (_button == GLFW_MOUSE_BUTTON_LEFT && _action == GLFW_RELEASE) {
		view->m_controller->m_mButtonLeft = false;
	}

	if (_button == GLFW_MOUSE_BUTTON_RIGHT && _action == GLFW_PRESS) {
		// Handle left mouse button click at position (xpos, ypos)
		view->m_controller->m_mButtonRight = true;
	} else if (_button == GLFW_MOUSE_BUTTON_RIGHT && _action == GLFW_RELEASE) {
		view->m_controller->m_mButtonRight = false;
	}
}
