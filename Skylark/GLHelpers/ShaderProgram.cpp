#include "stdafx.h"
#include "ShaderProgram.h"


GLuint ShaderProgram::getId()
{
	return mId;
}

void ShaderProgram::Use()
{
	glUseProgram(mId);
}

void ShaderProgram::AttachShader(Shader* shader)
{
	glAttachShader(mId, shader->getId());
	attachedShaders.push_back(shader->getId());
}

void ShaderProgram::Link()
{
	glLinkProgram(mId);

	GLint isLinked = 0;
	glGetProgramiv(mId, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &maxLength);
		//The maxLength includes the NULL character
		char buffer[512];
		glGetProgramInfoLog(mId, 512, NULL, buffer);
		//We don't need the program anymore.
		glDeleteProgram(mId);
		//Don't leak shaders either.
		//Use the infoLog as you see fit.
		//In this simple program, we'll just leave
		throw std::exception(buffer);
	}
	//Always detach shaders after a successful link.
	DetachShaders();
}

ShaderProgram::ShaderProgram()
{
	mId = glCreateProgram();
}


ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::DetachShaders()
{
	for (auto it = attachedShaders.begin(); it != attachedShaders.end(); it++)
	{
		glDetachShader(mId, *it);
	}

	attachedShaders.clear();
}
