#include "TextureManager.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>


TextureManager::TextureManager(const std::string& fileName)
{
	int width;
	int height;
	int numComponents;

	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		std::cerr << "texture load failed" << fileName << std::endl;
	}

	glGenTextures(1, &texHandler); //number of and address of texture
	glBindTexture(GL_TEXTURE_2D, texHandler); //bind texture, define type and specify the texture we are working on

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //wrap texture outside height
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //texture filterning for minification (texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //texture filtering for magnification(texture is larger than area)

																	  //send texture to gpu
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	//delete data from cpu
	stbi_image_free(imageData);


}


TextureManager::~TextureManager()
{
	//delete our textures
	glDeleteTextures(1, &texHandler); //number of and address of texture


}

void TextureManager::BindTexture(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31); //check to see if we are working with 1 of the 32 textures

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texHandler); // type of and texture to bind to unit

}