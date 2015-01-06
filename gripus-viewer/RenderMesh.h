#pragma once

#include <MemoryMesh.h>

#include <glm/glm.hpp>

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GLFW/glfw3.h>

class RenderMesh {
public:
	RenderMesh(MemoryMesh* mesh);
	~RenderMesh();

	MemoryMesh* getMemoryMesh();

	void initialize();
	void render(GLuint texUniformLocation);
	void finalize();
private:
	MemoryMesh* mesh;

	struct RenderEntry {
		GLuint vao;
		GLuint vbo;
		GLuint ibo;
		unsigned int elements;

		bool hasTexture;
		GLuint texture;
	};
	std::vector<RenderEntry*> entries;
};