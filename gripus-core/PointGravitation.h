#pragma once

#include "IGravitation.h"
#include "IXmlSerializable.h"

class PointGravitation : public IGravitation {
public:
	PointGravitation();
	PointGravitation(glm::vec3 position, float acceleration);
	virtual ~PointGravitation();

	virtual glm::vec3 getForce(float mass, glm::vec3 position);

	glm::vec3 position;
	float acceleration;

	serialization();
};

