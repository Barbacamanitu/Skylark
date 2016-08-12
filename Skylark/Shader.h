#pragma once
#include <string>
class Shader
{
public:
	Shader();
	~Shader();
	void loadFromFile(const std::string filename);
	void compile();
};

