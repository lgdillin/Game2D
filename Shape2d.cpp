#include "Shape2d.hpp"

Shape2d::Shape2d(glm::vec3 _pos, glm::vec3 _scale, bool _anc, float _angle, HeightZone _zone)
	: ShapeGeneric(_pos, _scale, _anc, _angle, _zone
) {
}

Shape2d::~Shape2d() {
}
