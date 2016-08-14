#include "stdafx.h"
#include "RenderWindow.h"
#include "GLHelpers/FileIO.h"

#include "GLHelpers/Shader.h"
#include "GLHelpers/ShaderProgram.h"

RenderWindow::RenderWindow()
{
	mIsOpen = false;
}


RenderWindow::~RenderWindow()
{
	Destroy();
}

void RenderWindow::HandleEvents()
{
	if (SDL_PollEvent(&windowEvent))
	{
		if (windowEvent.type == SDL_QUIT)
		{
			Close();
		};
	}
	
	glEnableVertexAttribArray(0);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
	SDL_GL_SwapWindow(sdlWindow);
	
	
}


bool RenderWindow::isOpen()
{
	return mIsOpen;
}

void RenderWindow::Close()
{
	SDL_DestroyWindow(sdlWindow);
	mIsOpen = false;
}

void RenderWindow::DrawTriangle()
{

	float vertices[] = {
		0.0f,  0.5f, // Vertex 1 (X, Y)
		0.5f, -0.5f, // Vertex 2 (X, Y)
		-0.5f, -0.5f  // Vertex 3 (X, Y)
	};

	theVertices = vertices;

	GLuint vbo;
	glGenBuffers(1, &vbo); // Generate 1 buffer

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	GLenum err = GL_NO_ERROR;
	err = glGetError();
	std::string vertexSource = FileIO::readFile("Shaders\\vertexShader.gl");
	std::string fragSource = FileIO::readFile("Shaders\\fragmentShader.gl");

	
	try
	{
	////NEW SHADER STUFF
		Shader vert;
		Shader frag;
		
		vert.createFromFile("Shaders\\vertexShader.gl",ShaderType::Vertex);
		frag.createFromFile("Shaders\\fragmentShader.gl", ShaderType::Fragment);
		sProg = new ShaderProgram();
		sProg->AttachShader(&vert);
		sProg->AttachShader(&frag);
		sProg->Link();
	}
	catch (std::exception ex)
	{
		int a = 1;
	}
	sProg->Use();
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLint posAttrib = glGetAttribLocation(sProg->getId() , "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	err = glGetError();
	glEnableVertexAttribArray(posAttrib);
	err = glGetError();
	

}

void RenderWindow::Initialize()
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	sdlWindow = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);

	if (sdlWindow != NULL)
	{
		/*
			If the window is not null, it was successfully created
			Create the open GL context here.
			TODO: Proper error checking and reporting
		*/
		glContext = SDL_GL_CreateContext(sdlWindow);
		mIsOpen = true;

		glewExperimental = GL_TRUE;
		glewInit();

		
	}
	
}

void RenderWindow::Destroy()
{
	
	SDL_GL_DeleteContext(glContext);
	Close();
	//delete sdlWindow;
	
	SDL_Quit();
}

