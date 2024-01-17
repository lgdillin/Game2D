#include "GlfwController.hpp"

GlfwController::GlfwController(GlfwGame &_game) {
	m_game = &_game;

	for (size_t i = 0; i < 1024; ++i) {
		m_keys[i] = false;
		m_keyHit[i] = false;
	}

	m_mButtonLeft = false;
	m_mButtonRight = false;

	m_firstMouseMovement = true;
	m_lastMouseX = 0.0f;
	m_lastMouseY = 0.0f;
	m_mouseDeltaX = 0.0f;
	m_mouseDeltaY = 0.0f;
	m_mouseX = 0.0f;
	m_mouseY = 0.0f;
}

GlfwController::~GlfwController() {
}

void GlfwController::keyControl(GLfloat _deltaTime) {
	GLfloat movementSpeed = 3.0f;
	GLfloat velocity = movementSpeed * _deltaTime;

	// sprint
	if (m_keys[GLFW_KEY_LEFT_SHIFT]) {
		velocity *= 8.0f;
	}

	bool movedY = false;
	bool movedX = false;
	glm::vec3 nPos = glm::vec3(0.0f, 0.0f, 0.0f);
	if (m_keys[GLFW_KEY_W]) {
		// Place holder for jump
		movedY = true;
		nPos.y = m_game->m_player.getPosition().y + 1.0 * velocity;
	} else if (m_keys[GLFW_KEY_S]) {
		// place holder for crouch
		movedY = true;
		nPos.y = m_game->m_player.getPosition().y - 1.0 * velocity;
	}

	if (m_keys[GLFW_KEY_D]) {
		movedX = true;
		nPos.x = m_game->m_player.getPosition().x + 1.0 * velocity;
	} else if (m_keys[GLFW_KEY_A]) {
		movedX = true;
		nPos.x = m_game->m_player.getPosition().x - 1.0 * velocity;
	}

	if (movedY || movedX) {
		float x = movedX ? nPos.x : m_game->m_player.getPosition().x;
		float y = movedY ? nPos.y : m_game->m_player.getPosition().y;

		m_game->movePlayer(x, y);
		m_game->moveCamera2D(x, y);
	}

	// Gravity
	if (m_keys[GLFW_KEY_G]) {
		if (m_keyHit[GLFW_KEY_G] == false) {
			m_keyHit[GLFW_KEY_G] = true;
			//setToggleGravity(!toggleGravity);
		}
	} else {
		m_keyHit[GLFW_KEY_G] = false;
	}

	// flashlight
	if (m_keys[GLFW_KEY_F]) {
		if (m_keyHit[GLFW_KEY_F] == false) {
			m_keyHit[GLFW_KEY_F] = true;
			//setToggleFlashlight(!toggleFlashLight);
		}
	} else {
		m_keyHit[GLFW_KEY_F] = false;
	}


	if (m_keys[GLFW_KEY_SPACE]) {
		//bumpCamera(glm::vec3(0.0f, 5.0f, 0.0f) * velocity);
	}
}

void GlfwController::mouseControl() {
	m_game->setCursorPosition(lastMouseX(), lastMouseY());
	return;

	// not relevant right now
	GLfloat turnSpeed = 0.4f;

	m_game->setYaw(m_game->yaw() + m_mouseDeltaX * turnSpeed);

	GLfloat pitch = m_game->pitch() + m_mouseDeltaY * turnSpeed;
	if (pitch > 89.0f) {
		m_game->setPitch(89.0f);
	} else if (pitch < -89.0f) {
		m_game->setPitch(-89.0f);
	} else {
		m_game->setPitch(pitch);
	}

	// zero out our deltas since the new angle is updated
	m_mouseDeltaX = 0.0f;
	m_mouseDeltaY = 0.0f;
}

void GlfwController::mouseClickControl() {
	if (m_mButtonLeft) {
		//std::cout << "left " << m_lastMouseX << " " << m_lastMouseY << std::endl;
		m_game->setCursorPosition(m_lastMouseX, m_lastMouseY);
	}

	if (m_mButtonRight) {
		//std::cout << "right" << m_lastMouseX << " " << m_lastMouseY << std::endl;
	}
}

void GlfwController::setKey(int _key, bool _state) {
	m_keys[_key] = _state;
}
