#pragma once

#include <string>
#include <ostream>

#include "Shader.h"

class ShaderProgram {
public:
	ShaderProgram();
	virtual ~ShaderProgram();

	bool link(std::ostream & err);
	unsigned int getProgram();

	Shader* vertexShader;
	Shader* fragmentShader;
private:
	unsigned int program;
};
