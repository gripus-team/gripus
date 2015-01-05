#pragma once

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

#include "Texture.h"

class TexturePool {
public:
	TexturePool() = delete;
	~TexturePool() = delete;

	static void initialize();
	static GLuint getTexture(std::string path);
	static unsigned int getSlot(GLuint object);
	static void finalize();
	
private:
	static unsigned int slots_count;
	static Texture** slots;

	static std::vector<Texture*> textures;
};