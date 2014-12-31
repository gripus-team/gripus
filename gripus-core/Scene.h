#pragma once

#include "IXmlSerializable.h"
#include "Mesh.h"

#include <vector>

class Scene : public IXmlSerializable {
public:
	Scene();
	Scene(std::vector<Mesh*> meshes);
	virtual ~Scene();

	std::vector<Mesh*> meshes;

	serialization();
};

