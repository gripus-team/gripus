/*
 * MemoryMesh.h
 *
 *  Created on: Jan 2, 2015
 *      Author: lexected
 */

#ifndef MEMORYMESH_H_
#define MEMORYMESH_H_

#include "Mesh.h"

#include <vector>
#include <string>

#include <glm/glm.hpp>

class MemoryMesh {
public:
	MemoryMesh(Mesh* mesh);
	virtual ~MemoryMesh();

	Mesh* getMesh();
	void load();

	struct MemoryEntry {
		struct Vertex {
			glm::vec4 vertex;
			glm::vec4 normal;
			glm::vec4 color;
			glm::vec4 texuv;
		};
		Vertex* vertices;
		unsigned vertices_count;

		struct Face {
			unsigned int a;
			unsigned int b;
			unsigned int c;
			//unsigned int d; //should be unused, we always triangulate
		};
		Face* faces;
		unsigned int faces_count;
		
		bool hasTexture;
		unsigned int textureIndex;
	};
	std::vector<MemoryEntry*> entries;
	
	std::vector<std::string> textures;
private:
	Mesh* mesh;
};

#endif /* MEMORYMESH_H_ */
