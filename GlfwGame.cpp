#include "GlfwGame.hpp"

GlfwGame::GlfwGame() {
	m_cameraPosition = glm::vec3(0.0f, 0.0f, 5.0f);
	m_right = glm::vec3(0.0f);
	m_front = glm::vec3(0.0f, 0.0f, -1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_pitch = 0.0f;
	m_yaw = -90.0f;
	m_roll = 0.0f;
	m_mouseX = 0.0f;
	m_mouseY = 0.0f;
	m_worldMouseX = 0.0f;
	m_worldMouseY = 0.0f;
	m_worldMouse = glm::vec2(0);
	m_maxLaserDist = 1000.0f;

	m_shapes = std::vector<ShapeGeneric *>();
}

GlfwGame::~GlfwGame() { 
}

void GlfwGame::initialize() {
	m_ray.intialize();
	builder::buildShapes(&m_shapes);

	m_player.setBody(m_shapes[m_shapes.size()-1]);
	moveCamera2D(m_player.getPosition().x, m_player.getPosition().y);
}

void GlfwGame::update() {

	for (auto &s : m_shapes) {
		if (s->m_heightZone == HeightZone::FLOOR) continue;

		// perform physics updates for objects in motion
		if (!s->m_anchored) {}

		// check collisions with other objects
		for (auto &s2 : m_shapes) {
			if (s == s2) continue;

			// Potentially poor design choice to do this here
			if (s->m_heightZone == s2->m_heightZone) {
				separatingAxisTheorem2(s, s2);
			}
		}
		// TODO: add a flag that is thrown whether or not we actually
		// need to compute a new bounding box (if the object has/hasn't moved)
		s->recomputeBoundingVolume();
	}
	
	// Compute the closest distance to the mouse coordinates
	calculateRaycaster();

	// turn the players body to look at the mouse
	turnPlayer();

	// recompute the camera's vectors for the render step
	recomputeCameraVectors();
}

void GlfwGame::separatingAxisTheorem2(ShapeGeneric *_a, ShapeGeneric *_b) {
	float overlap = INFINITY;
	int nNormals = _a->m_normals.size() + _b->m_normals.size();
	bool separatingAxis = false;
	for (int i = 0; i < nNormals; ++i) {
		glm::vec3 norm = i < _a->m_normals.size() ? _a->m_normals[i] : _b->m_normals[i - _a->m_normals.size()];

		float aMin = math2d::dot2d(norm.x, norm.y, _a->m_points[0].x, _a->m_points[0].y);
		float aMax = aMin;
		for (auto &p : _a->m_points) {
			float v = math2d::dot2d(norm.x, norm.y, p.x, p.y);
			if (v < aMin) aMin = v;
			if (v > aMax) aMax = v;
		}

		float bMin = math2d::dot2d(norm.x, norm.y, _b->m_points[0].x, _b->m_points[0].y);
		float bMax = bMin;
		for (auto &p : _b->m_points) {
			float v = math2d::dot2d(norm.x, norm.y, p.x, p.y);
			if (v < bMin) bMin = v;
			if (v > bMax) bMax = v;
		}

		overlap = std::min(std::min(aMax, bMax) - std::max(aMin, bMin), overlap);

		if (!(aMax > bMin && aMin < bMax)) {
			separatingAxis = true;
			break;
		}
	}

	if (separatingAxis) {} else {
		if (!_a->m_anchored) {
			float displaceX = _b->m_position.x - _a->m_position.x;
			float displaceY = _b->m_position.y - _a->m_position.y;
			float length = math2d::eucDist(displaceX, displaceY);
			_a->m_position.x -= overlap * displaceX / length;
			_a->m_position.y -= overlap * displaceY / length;
		}
	}
}

float GlfwGame::signedDistToScene(ShapeGeneric *_s, glm::vec2 _v) {
	glm::vec2 inverseTransform = math2d::inverseTransform(_v, _s->m_position, _s->m_angleRad);
	float x = math2d::sdfBox(inverseTransform, glm::vec2(_s->m_scale.x, _s->m_scale.y));
	return x;
}


void GlfwGame::calculateRaycaster() {
	float epsilon = 0.000001f;
	float dist = m_maxLaserDist;

	glm::vec2 ray = m_worldMouse - glm::vec2(m_player.getPosition().x, m_player.getPosition().y);
	glm::vec2 nRay = glm::normalize(ray);
	float magnitude = math2d::eucDist(nRay);
	glm::vec2 v0 = m_player.getPosition();
	int i = 0;
	while (true) {
		for (auto &s : m_shapes) {
			if (s == m_player.getBody()) continue;
			if (s->m_heightZone != HeightZone::LOWERBODY) continue;
			float d = signedDistToScene(s, v0);
			dist = glm::min(dist, d);
		}

		// walk along the ray created between the player and the mouse
		// for that given distance
		float t = (magnitude != 0) ? dist / math2d::eucDist(nRay) : 0;
		float x = v0.x + t * nRay.x;
		float y = v0.y + t * nRay.y;
		// Check cases to see if we have collided with something
		// 1: distance traverse is too small
		float e = math2d::eucDist(x - v0.x, y - v0.y);
		if (dist < epsilon) {
			v0.x = x;
			v0.y = y;
			break;
		}

		float distToMouse = math2d::eucDist(m_worldMouse - v0);
		if (distToMouse < dist) {
			v0.x = m_worldMouse.x;
			v0.y = m_worldMouse.y;
			break;
		}

		if (i > 1000) { 
			break; 
		}

		v0.x = x;
		v0.y = y;
		++i;
	}

	m_ray.setDot(v0.x, v0.y);
}

void GlfwGame::turnPlayer() {
	glm::vec2 lookDirection = glm::normalize(m_worldMouse 
		- glm::vec2(m_player.getPosition().x, m_player.getPosition().y));
	glm::vec2 north = glm::vec2(0.0f, 1.0f);
	float angle = glm::acos(glm::dot(lookDirection, north));
	float cross = (lookDirection.x * north.y);
	if (cross > 0.0f) { angle = -angle; }

	std::cout << angle << std::endl;
	
	m_player.getBody()->m_angleRad = std::fmod(angle, 2 * glm::pi<float>());
}

void GlfwGame::setCursorPosition(GLfloat _mouseX, GLfloat _mouseY) {
	m_mouseX = _mouseX;
	m_mouseY = _mouseY;
}

void GlfwGame::setWorldMousePos(float _x, float _y) {
	m_worldMouseX = _x;
	m_worldMouseY = _y;
	m_worldMouse.x = _x;
	m_worldMouse.y = _y;
}

void GlfwGame::movePlayer(float _x, float _y) {
	m_player.move(_x, _y);
	m_cameraPosition.x = _x;
	m_cameraPosition.y = _y;
}

void GlfwGame::moveCamera2D(float _x, float _y) {
	m_cameraPosition.x = _x;
	m_cameraPosition.y = _y;
}

void GlfwGame::recomputeCameraVectors() {
	m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front.y = sin(glm::radians(m_pitch));
	m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(m_front);

	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_right = glm::normalize(glm::cross(m_front, worldUp));

	m_up = glm::normalize(glm::cross(m_right, m_front));
}
