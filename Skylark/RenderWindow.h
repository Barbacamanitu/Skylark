#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

class RenderWindow
{
public:
	RenderWindow();
	~RenderWindow();
	void Initialize();
	void HandleEvents();

	bool isOpen();
	void Close();

	void DrawTriangle();
private:
	
	void Destroy();

	SDL_Window* sdlWindow;
	SDL_GLContext glContext;

	SDL_Event windowEvent;
	bool mIsOpen;

	int otherfunc();
	float* theVertices;
	
};

