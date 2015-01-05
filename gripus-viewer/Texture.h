#pragma once

#include <string>

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GLFW/glfw3.h>

class Texture {
public:
	Texture(GLuint object, std::string path);
	~Texture();

	std::string getPath();
	GLuint getObject();

private:
	GLuint object;
	std::string path;
};