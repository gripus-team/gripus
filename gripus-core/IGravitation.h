#pragma once

#include <glm/glm.hpp>

#include "IXmlSerializable.h"

class IGravitation : public IXmlSerializable
{
public:
	virtual ~IGravitation() = default;

	virtual glm::vec3 getForce(float mass, glm::vec3 position) = 0;

	sph() = 0;
	dsph() = 0;
	static IGravitation* getGravitation(TiXmlElement* myElement);

protected:
	IGravitation() = default;
};

