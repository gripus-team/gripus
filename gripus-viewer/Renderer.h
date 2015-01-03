#include <iostream>
#include <string>
#include <vector>

#include <Simulation.h>
#include <Output.h>

#include "RenderMesh.h"

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GLFW/glfw3.h>

class Renderer {
public:
	Renderer(std::vector<RenderMesh*> meshes);
	virtual ~Renderer();

	void initialize();
	void render();
	void finalize();

private:
	std::vector<RenderMesh*> meshes;
};
