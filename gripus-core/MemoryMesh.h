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

class MemoryMesh {
public:
	MemoryMesh(Mesh* mesh);
	virtual ~MemoryMesh();

	Mesh* getMesh();
	void load();

	struct Entry {
		struct Vertex {
			float vertex[4];
			float normal[4];
			float color[4];
			float texcoord[4];
		};
		Vertex* vertices;
		unsigned vertices_count;

		struct Face {
			unsigned int a;
			unsigned int b;
			unsigned int c;
			//unsigned int d; //should be unused
		};
		Face* faces;
		unsigned int faces_count;
	};
	std::vector<Entry*> entries;
private:
	Mesh* mesh;
};

#endif /* MEMORYMESH_H_ */
