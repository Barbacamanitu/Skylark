// Skylark.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RenderWindow.h"

int main(int argc, char *argv[])
{
	RenderWindow rWindow;
	rWindow.Initialize();

	while (rWindow.isOpen())
	{
		rWindow.HandleEvents();
	}
	
	return 0;
}

