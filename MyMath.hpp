#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

namespace math2d {
	static float dot2d(float _x1, float _y1, float _x2, float _y2) {
		return (_x1 * _x2) + (_y1 * _y2);
	}

	static float eucDist(float _x, float _y) {
		return glm::sqrt(_x * _x + _y * _y);
	}

	static float eucDist(glm::vec2 _v) {
		return glm::sqrt(_v.x * _v.x + _v.y * _v.y);
	}

	static glm::vec2 normalizeVec2d(float _x, float _y) {
		float length = eucDist(_x, _y);
		return glm::vec2(_x / length, _y / length);
	}

	static float cross2d(glm::vec2 _v1, glm::vec2 _v2) {
		return (_v1.x * _v2.y - _v2.x * _v1.y);
	}

	static glm::vec2 maxVec2(glm::vec2 _v, float _c) {
		return glm::vec2(glm::max(_v.x, _c), glm::max(_v.y, _c));
	}

	static glm::vec2 minVec2(glm::vec2 _v, float _c) {
		return glm::vec2(glm::min(_v.x, _c), glm::min(_v.y, _c));
	}

	static glm::vec2 inverseVec2(glm::vec2 _v) {
		return glm::vec2(-_v.y, _v.x);
	}

	static glm::vec2 inverseTransform(glm::vec2 _p, glm::vec2 _translate, float _angleRad) {
		glm::vec2 v{ _p.x - _translate.x, _p.y - _translate.y };

		float x = v.x * cos(_angleRad) - v.y * sin(_angleRad);
		float y = -v.x * sin(-_angleRad) + v.y * cos(_angleRad);

		v.x = x;
		v.y = y;

		return v;
	}

	static float sdfBox(glm::vec2 _p, glm::vec2 _corner) {
 		float qx = abs(_p.x) - _corner.x;
		float qy = abs(_p.y) - _corner.y;
		
		float dOutside = eucDist(glm::max(qx, 0.0f), glm::max(qy, 0.0f));
		//float dInside = glm::min(glm::max(qx, qy), 0.0f);
		float dInside = glm::max(glm::min(qx, 0.0f), glm::min(qy, 0.0f));
		return dOutside + dInside;
	}
};

namespace math3d {

};