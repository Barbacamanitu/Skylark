// Skylark.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RenderWindow.h"
#include <string>

int main(int argc, char *argv[])
{

	

	RenderWindow* rWindow = new RenderWindow();
	rWindow->Initialize();
	rWindow->DrawTriangle();

	

	std::string e = "earl sucks dicks";
	std::string r = "russ sux diks";

	while (rWindow->isOpen())
	{
		rWindow->HandleEvents();
	}

	

	return 0;
}

