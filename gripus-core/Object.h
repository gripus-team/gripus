#pragma once

#include <glm/glm.hpp>

#include "IXmlSerializable.h"

class Object : public IXmlSerializable
{
public:
	Object();
	Object(std::string id, std::string mesh, float mass, float charge, glm::vec3 position, glm::vec3 centerOfMass, glm::vec3 velocity, glm::vec3 orientation, glm::vec3 rotation);
	Object(Object* object); // a cloning constructor
	virtual ~Object();

	std::string id;
	std::string mesh;

	float mass;
	glm::vec3 centerOfMass;
	float charge;
	
	glm::vec3 position;
	glm::vec3 orientation;
	glm::vec3 rotation;
	
	glm::vec3 velocity;

	serialization();
};

