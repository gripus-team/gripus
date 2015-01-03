#include <MemoryMesh.h>

#include <glm/glm.hpp>

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GLFW/glfw3.h>

class RenderMesh {
public:
	RenderMesh(MemoryMesh* mesh);
	~RenderMesh();

	void initialize();
	void render(glm::mat4 model);
	void finalize();
private:
	MemoryMesh* mesh;
	GLuint vao;
	GLuint* vbo;
	unsigned int elements; //number of vertex indexes to draw, in all entities of this object
};