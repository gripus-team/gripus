#pragma once

#include <string>
#include <ostream>

class Shader {
public:
	virtual ~Shader();
	
	bool compile(std::ostream & err);
	unsigned int getShader();

	static Shader* load(std::string path, unsigned int shaderType);

protected:
	Shader(const char* shaderCode, unsigned int shaderType);

private:
	unsigned int shader;
	unsigned int shaderType;
	const char* shaderCode;
};

