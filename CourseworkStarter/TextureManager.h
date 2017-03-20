#pragma once
#include <string>
#include <GL\glew.h>

class TextureManager
{
public:
	TextureManager(const std::string& fileName);

	void BindTexture(unsigned int unit); // bind upto 32 textures

	~TextureManager();

protected:
private:

	GLuint texHandler;
};


