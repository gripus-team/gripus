#pragma once

#include "IXmlSerializable.h"

#include <glm/glm.hpp>

class View : public IXmlSerializable {
public:
	View();
	View(glm::vec3 eye, glm::vec3 center, glm::vec3 up, float step);
	virtual ~View();

	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;
	float step;

	serialization();
};

