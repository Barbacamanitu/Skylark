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

void Shader::loadFromFile(const std::string filename)
{
	const char* source = FileIO::readFile(filename.c_str()).c_str();
	GLchar* glSource = (GLchar*)source;

	std::string extension = filename.substr(filename.find_last_of(".") + 1);
	if (extension == "fragment")
	{
		//Compile a fragment shader
	}



	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	
}

void Shader::compile()
{

}
