#pragma once
#include "Shader.h"
#include <vector>
class ShaderProgram
{
public:
	GLuint getId();
	void Use();
	void AttachShader(Shader* shader);
	void Link();
	ShaderProgram();
	~ShaderProgram();
private:
	GLuint mId;
	std::vector<GLuint> attachedShaders;
	void DetachShaders();
};

