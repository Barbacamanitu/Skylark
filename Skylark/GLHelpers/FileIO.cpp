#include "stdafx.h"
#include "FileIO.h"
#include <fstream>


std::string FileIO::readFile(const std::string filename)
{
	std::ifstream infile(filename);
	std::string str((std::istreambuf_iterator<char>(infile)),
		std::istreambuf_iterator<char>());
	return str;
}

FileIO::FileIO()
{
}


FileIO::~FileIO()
{
}
