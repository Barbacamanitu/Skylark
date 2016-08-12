#pragma once
class Shader
{
public:
	Shader();
	~Shader();
	void loadFromFile(const char* filename);
	void compile();
};

