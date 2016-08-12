#include "stdafx.h"
#include "RenderWindow.h"
#include "GLHelpers/FileIO.h"

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

	const GLchar* vSource = (const GLchar*)vertexSource.c_str();
	const GLchar* fSource = (const GLchar*)fragSource.c_str();
	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vSource, NULL);
	err = glGetError();
	glCompileShader(vertexShader);
	err = glGetError();
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	err = glGetError();
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);	
		throw std::exception(buffer);
	}
	err = glGetError();


	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fSource, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);	
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	err = glGetError();

	glUseProgram(shaderProgram);
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
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

