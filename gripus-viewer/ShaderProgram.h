#pragma once

#include <vector>
#include <string>
#include <ostream>

#include "Shader.h"

class ShaderProgram {
public:
	ShaderProgram();
	virtual ~ShaderProgram();

	void bind_location(std::string name, unsigned int index);
	bool link(std::ostream & err);
	unsigned int getProgram();

	Shader* vertexShader;
	Shader* fragmentShader;
private:
	unsigned int program;
	std::vector<std::string> attributes;
};
