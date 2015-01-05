#include <iostream>
#include <map>

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"

class ShaderProgramFond {
public:
	ShaderProgramFond() = delete;
	~ShaderProgramFond() = delete;

	static bool initialize();
	static GLuint getProgram(std::string poolName);
	static void finalize();

private:
	std::map<std::string, ShaderProgram*> programs;
};