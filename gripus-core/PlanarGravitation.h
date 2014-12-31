#pragma once

#include "IGravitation.h"

class PlanarGravitation : public IGravitation {
public:
	PlanarGravitation();
	PlanarGravitation(glm::vec3 position, glm::vec3 acceleration);
	virtual ~PlanarGravitation();

	virtual glm::vec3 getForce(float mass, glm::vec3 position);

	glm::vec3 position;
	glm::vec3 acceleration;

	serialization();
};

