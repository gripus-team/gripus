#pragma once

#include <string>

#include "IXmlSerializable.h"

class Mesh : public IXmlSerializable {
public:
	Mesh();
	Mesh(std::string name, std::string path, glm::mat4 transform);
	virtual ~Mesh();

	std::string name;
	std::string path;
	glm::mat4 transform;

	serialization();
};

