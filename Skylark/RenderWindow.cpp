#include "stdafx.h"
#include "RenderWindow.h"


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

		GLuint vertexBuffer;
		glGenBuffers(1, &vertexBuffer);

		printf("%u\n", vertexBuffer);
	}
	
}

void RenderWindow::Destroy()
{
	
	SDL_GL_DeleteContext(glContext);
	Close();
	//delete sdlWindow;
	
	SDL_Quit();
}
