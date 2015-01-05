#include "TexturePool.h"

#include <iostream>	//why does that idiot include iostream everywhere? maybe because he is not able to write a normal error reporting? You IDIOT, I admire you! You are just like ME!
#include <cstdio>	//this one is here for the image loading
#include <stb_image.h>

#include <cstring>

unsigned int TexturePool::slots_count;
Texture** TexturePool::slots;
std::vector<Texture*> TexturePool::textures;
	
void TexturePool::initialize() {
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, (GLint*)&slots_count);
	slots = new Texture*[slots_count];
	memset(slots, (int)nullptr, slots_count*sizeof(Texture*));
}
GLuint TexturePool::getTexture(std::string path) {
	for(Texture* t : textures)
		if(t->getPath()==path)
			return t->getObject();

	GLuint texture;
	glGenTextures(1, &texture);
	textures.push_back(new Texture(texture, path));

	glActiveTexture(GL_TEXTURE0 + getSlot(texture));
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	FILE* f = fopen(path.c_str(), "rb");
	if(!f) {
		std::cerr << "Failed to load the texture \"" << path.c_str() << "\", file not found" << std::endl;
		return texture;
	}

	int width, height, components;
	unsigned char* data = stbi_load_from_file(f, &width, &height, &components, 0);
	if(!data) {
		std::cerr << "Failed to load the texture \"" << path.c_str() << "\", " << stbi_failure_reason() << std::endl;
		return texture;
	}

	GLenum what;
	if(components==4)
		what = GL_RGBA;
	else if(components==3)
		what = GL_RGB;
	else if(components==2)
		what = GL_LUMINANCE_ALPHA;
	else
		what = GL_LUMINANCE;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, what, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
	fclose(f);

	return texture;
}
unsigned int TexturePool::getSlot(GLuint object) {
	unsigned int i; unsigned int nulli = slots_count;
	for(i = 0;i < slots_count;i++) {
		if(slots[i]==nullptr) {
			if(nulli==slots_count)
				nulli = i;
		} else if(slots[i]->getObject()==object)
			return i;
	}

	Texture* theTexture = nullptr;
	for(Texture* t : textures)
		if(t->getObject() == object) {
			theTexture = t;
			break;
		}

	if(nulli != slots_count) {
		slots[nulli] = theTexture;
		return nulli;
	}

	static unsigned int renew_counter = 0;
	if(renew_counter == slots_count)
		renew_counter = 0;

	slots[renew_counter] = theTexture;
	return renew_counter++;
}
void TexturePool::finalize() {
	for(Texture* t : textures)
		delete t;

	delete[] slots;
}