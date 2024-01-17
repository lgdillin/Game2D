#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "ShapeGeneric.hpp"

namespace builder {
	static void buildShapes(std::vector<ShapeGeneric *> *_shapes) {


		//Triangle *triangle = new Triangle(glm::vec3(-2.0f, 2.0f, 1.0f),
		//	glm::vec3(1.0f, 1.0f, 1.0f), true, 0.0f, HeightZone::LOWERBODY);
		//triangle->initialize();
		//_shapes->push_back(triangle);

		//Rectangle *rectangle = new Rectangle(glm::vec3(0.0f, 0.0f, 1.0f), 
		//	glm::vec3(3.0f, 1.0f, 1.0f), true, 0.0f, HeightZone::LOWERBODY);
		//rectangle->initialize();
		//_shapes->push_back(rectangle);

		Box *rightSide = new Box(glm::vec3(4.0f, 0.0f, 1.0f),
			glm::vec3(1.0f, 3.0f, 1.0f), true, 0.0f, HeightZone::LOWERBODY);
		rightSide->initialize();
		_shapes->push_back(rightSide);

		Box *bottomSide = new Box(glm::vec3(0.0f, -4.0f, 1.0f),
			glm::vec3(5.0f, 1.0f, 1.0f), true, 0.0f, HeightZone::LOWERBODY);
		bottomSide->initialize();
		_shapes->push_back(bottomSide);

		Box *leftSide = new Box(glm::vec3(-4.0f, 0.0f, 1.0f),
			glm::vec3(1.0f, 3.0f, 1.0f), true, 0.0f, HeightZone::LOWERBODY);
		leftSide->initialize();
		_shapes->push_back(leftSide);

		Box *topLeft = new Box(glm::vec3(-2.0f, 6.0f, 1.0f),
			glm::vec3(1.0f, 3.0f, 1.0f), true, 0.0f, HeightZone::LOWERBODY);
		topLeft->initialize();
		_shapes->push_back(topLeft);

		Box *topRight = new Box(glm::vec3(2.0f, 6.0f, 1.0f),
			glm::vec3(1.0f, 3.0f, 1.0f), true, 0.0f, HeightZone::LOWERBODY);
		topRight->initialize();
		_shapes->push_back(topRight);


		/// Objects with transparency


		Rectangle *floor = new Rectangle(glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(3.0f, 3.0f, 1.0f), true, 0.0f, HeightZone::FLOOR, "dirt");
		floor->initialize();
		_shapes->push_back(floor);

		Rectangle *floor1 = new Rectangle(glm::vec3(0.0f, 6.0f, 0.0f),
			glm::vec3(3.0f, 4.0f, 1.0f), true, 0.0f, HeightZone::FLOOR, "dirt");
		floor1->initialize();
		_shapes->push_back(floor1);

		Rectangle *rotatedRectangle = new Rectangle(glm::vec3(2.0f, 3.5f, 1.0f),
			glm::vec3(0.5f, 0.5f, 1.0f), false, 45.0f, HeightZone::LOWERBODY, "rusty");
		rotatedRectangle->initialize();
		_shapes->push_back(rotatedRectangle);

		Cir

		Rectangle *playerBody = new Rectangle(glm::vec3(0.0f, 3.0f, 1.0f),
			glm::vec3(0.4f, 0.4f, 1.0f), false, 0.0f, HeightZone::LOWERBODY, "police1");
		playerBody->initialize();
		_shapes->push_back(playerBody);
	}
}