#include "ShaderProgram.h"

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GLFW/glfw3.h>

ShaderProgram::ShaderProgram()
	: program(0), attributes(16), vertexShader(nullptr), fragmentShader(nullptr) {

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

void ShaderProgram::bind_location(std::string name, unsigned int index) {
	this->attributes[index] = name;
}
bool ShaderProgram::link(std::ostream & err) {
	this->program = glCreateProgram();
	
	glAttachShader(this->program, this->vertexShader->getShader());
	glAttachShader(this->program, this->fragmentShader->getShader());

	GLuint i = 0;
	for(std::string attribute : attributes) {
		if(attribute!="")
			glBindAttribLocation(this->program, i, attribute.c_str());
		i++;
	}

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
