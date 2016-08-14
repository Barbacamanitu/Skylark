#include "stdafx.h"
#include "Shader.h"
#include "FileIO.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <vector>


Shader::Shader()
{
	
}

Shader::~Shader()
{
}


void Shader::createFromFile(const std::string filename, ShaderType sType)
{
	std::string s = FileIO::readFile(filename);
	const GLchar* source = s.c_str();
	switch (sType)
	{
		case ShaderType::Fragment:
			mId = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		case ShaderType::Vertex:
			mId = glCreateShader(GL_VERTEX_SHADER);
			break;
		default:
			throw std::exception("Unknown Shader Type");
			break;
	}
	glShaderSource(mId, 1, &source, 0);
	glCompileShader(mId);

	GLint isCompiled = 0;
	glGetShaderiv(mId, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(mId, GL_INFO_LOG_LENGTH, &maxLength);
		//The maxLength includes the NULL character
		char buffer[512];
		glGetShaderInfoLog(mId, 512, NULL, buffer);
		//We don't need the shader anymore.
		glDeleteShader(mId);
		//Use the infoLog as you see fit.
		//In this simple program, we'll just leave
		throw std::exception(buffer);
	}
}

GLint Shader::getId()
{
	return mId;
}

ShaderType Shader::getType()
{
	return mShaderType;
}

