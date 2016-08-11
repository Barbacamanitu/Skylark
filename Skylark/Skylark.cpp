// Skylark.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SDL.h>

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Delay(1000);

	SDL_Quit();
	return 0;
}

