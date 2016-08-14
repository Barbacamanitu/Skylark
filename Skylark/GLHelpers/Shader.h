#pragma once
#include <string>
#include "GL\glew.h"
enum ShaderType
{
	Fragment,
	Vertex
};
class Shader
{
public:
	Shader();
	~Shader();	
	void createFromFile(const std::string filename, ShaderType sType);
	GLint getId();
	ShaderType getType();
private:
	GLuint mId;
	ShaderType mShaderType;
	
};

