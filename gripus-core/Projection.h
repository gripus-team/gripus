#pragma once

#include "IXmlSerializable.h"
#include <glm/glm.hpp>

class Projection : public IXmlSerializable {
public:
	enum ProjectionType {
		Parallel,
		Perspective
	};
	
	Projection();
	Projection(ProjectionType type, glm::mat3x2 size, glm::vec3 scale);
	virtual ~Projection();

	ProjectionType type;
	glm::mat3x2 size;
	glm::vec3 scale;

	serialization();
};

