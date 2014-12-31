#include "ShaderProgram.h"

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GLFW\glfw3.h>
//#include <wglext.h>
#include <glext.h>

ShaderProgram::ShaderProgram()
	: program(0), vertexShader(nullptr), fragmentShader(nullptr) {
		
}
ShaderProgram::~ShaderProgram() {
	//detach shaders
	if (this->program != 0) {
		if (this->vertexShader != nullptr) {
			glDetachShader(this->program, this->vertexShader->getShader());
			delete this->vertexShader;
		}
		if (this->fragmentShader != nullptr) {
			glDetachShader(this->program, this->fragmentShader->getShader());
			delete this->vertexShader;
		}

		glDeleteProgram(this->program);
	}
}

bool ShaderProgram::link(std::ostream & err) {
	this->program = glCreateProgram();

	glAttachShader(this->program, this->vertexShader->getShader());
	glAttachShader(this->program, this->fragmentShader->getShader());

	glLinkProgram(this->program);

	GLint howItEnded;
	glGetShaderiv(this->program, GL_LINK_STATUS, &howItEnded);
	if (howItEnded == GL_FALSE) {
		glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &howItEnded);

		GLchar* info = new GLchar[howItEnded];
		glGetProgramInfoLog(this->program, howItEnded, &howItEnded, info);
		err << info << std::endl;

		delete[] info;
		return false;
	}

	return true;
}
unsigned int ShaderProgram::getProgram() {
	return this->program;
}