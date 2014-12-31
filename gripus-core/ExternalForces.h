#pragma once

#include "IXmlSerializable.h"
#include "Time.h"
#include "ExternalForce.h"
#include "Object.h"

#include <vector>

class ExternalForces : public IXmlSerializable {
public:
	ExternalForces();
	ExternalForces(std::vector<ExternalForce*> forces);
	virtual ~ExternalForces();

	glm::vec3 getForce(Object* object, Time* t = nullptr);

	std::vector<ExternalForce*> forces;

	serialization();
};

