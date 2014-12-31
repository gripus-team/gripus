#pragma once

#include <vector>

#include "Object.h"
#include "IGravitation.h"

#include "IXmlSerializable.h"

class Environment : public IXmlSerializable
{
public:
	Environment();
	Environment(std::vector<IGravitation*> gravitations);
	virtual ~Environment();

	glm::vec3 getForce(Object* obj);

	std::vector<IGravitation*> gravitations;

	serialization();
};

