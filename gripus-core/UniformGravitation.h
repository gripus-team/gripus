#pragma once

#include "IGravitation.h"

class UniformGravitation : public IGravitation
{
public:
	UniformGravitation();
	UniformGravitation(glm::vec3 acceleration);
	virtual ~UniformGravitation();

	virtual glm::vec3 getForce(float mass, glm::vec3 position);

	glm::vec3 acceleration;

	serialization();
};

