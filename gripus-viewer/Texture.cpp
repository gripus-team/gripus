#include "Texture.h"

Texture::Texture(GLuint object, std::string path)
	: object(object), path(path) {

}
Texture::~Texture() {
	glDeleteTextures(1, &this->object);
}

std::string Texture::getPath() {
	return this->path;
}
GLuint Texture::getObject() {
	return this->object;
}