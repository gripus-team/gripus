#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <Simulation.h>

#include "RenderMesh.h"

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GLFW/glfw3.h>

class Renderer {
public:
	Renderer() = delete;
	virtual ~Renderer() = delete;

	static void initialize(Simulation* simulation);
	static void render(GLuint modelUniformLocation, GLuint texUniformLocation);
	static void finalize();

private:
	struct RenderPair {
		Object* object;
		RenderMesh* mesh;
	};
	static std::vector<RenderPair> pairs;
};
