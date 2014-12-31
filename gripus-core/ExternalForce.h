#pragma once

#include "IXmlSerializable.h"

#include <glm\glm.hpp>

class ExternalForce : public IXmlSerializable {
public:
	ExternalForce();
	ExternalForce(std::string object, glm::vec3 force, float startTime, float endTime);
	virtual ~ExternalForce();

	std::string object;
	glm::vec3 force;
	float startTime;
	float endTime;

	serialization();
};

