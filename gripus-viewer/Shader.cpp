#include "Shader.h"

#include <fstream>

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GLFW/glfw3.h>

Shader::Shader(const char* shaderCode, unsigned int shaderType)
	: shader(0), shaderCode(shaderCode), shaderType(shaderType) {
		
}
Shader::~Shader() {
	if (this->shader != 0)
		glDeleteShader(this->shader);

	delete[] shaderCode;
}

bool Shader::compile(std::ostream & err) {
	this->shader = glCreateShader(this->shaderType);
	glShaderSource(this->shader, 1, (const GLchar**)&this->shaderCode, 0);
	glCompileShader(this->shader);

	GLint howItEnded;
	glGetShaderiv(this->shader, GL_COMPILE_STATUS, &howItEnded);
	if (howItEnded == GL_FALSE) {
		glGetShaderiv(this->shader, GL_INFO_LOG_LENGTH, &howItEnded);

		GLchar* info = new GLchar[howItEnded];
		glGetShaderInfoLog(this->shader, howItEnded, &howItEnded, info);
		err << info << std::endl;

		delete[] info;
		return false;
	}

	return true;
}
unsigned int Shader::getShader() {
	return this->shader;
}

Shader* Shader::load(std::string shaderFile, unsigned int shaderType) {
	std::ifstream file(shaderFile, std::ios::in | std::ios::binary | std::ios::ate);
	unsigned int length = (unsigned int)file.tellg();

	file.seekg(0, std::ios_base::beg);
	char* shaderCode = new char[length+1];
	file.read(shaderCode, length);
	shaderCode[length] = '\0';

	return new Shader(shaderCode, shaderType);
}
