#include "stdafx.h"
#include "Shader.h"
#include "./GLHelpers/FileIO.h"
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>


Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::loadFromFile(const char* filename)
{
	const char* source = FileIO::readFile(filename).c_str();
	GLchar* glSource = (GLchar*)source;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	
}

void Shader::compile()
{

}
