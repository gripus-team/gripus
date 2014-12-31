#pragma once

#include <vector>

#include "IXmlSerializable.h"
#include "Object.h"

class System : public IXmlSerializable {
public:
	System();
	System(std::vector<Object*> objects);
	virtual ~System();

	virtual glm::vec3 getForce(Object* obj, Object* parent = nullptr);

	std::vector<Object*> objects;

	serialization();
};

