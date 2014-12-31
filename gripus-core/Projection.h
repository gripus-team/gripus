#pragma once

#include "IXmlSerializable.h"
#include <glm\glm.hpp>

class Projection : public IXmlSerializable {
public:
	enum ProjectionType;

	Projection();
	Projection(ProjectionType type, glm::mat3x2 size);
	virtual ~Projection();

	enum ProjectionType {
		Parallel,
		Perspective
	} type;
	glm::mat3x2 size;

	serialization();
};

