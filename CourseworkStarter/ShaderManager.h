#pragma once
#include <string>
#include <GL\glew.h>
#include "Transform.h"
#include "View.h"
class ShaderManager
{
public:
	ShaderManager(const std::string& filename);
	~ShaderManager();

	void BindShader(); //Set gpu to use our shaders

	std::string LoadShaderFromFile(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	void Update(const Transform& trans, const View& camera);
	


protected:
private:
	static const unsigned int NUM_OF_SHADERS = 2; // number of shaders

	enum
	{
		TRANSFORM_UNIF,

		NUM_OF_UNIFORMS
	};

	GLuint shaderProg; // Track the shader program
	GLuint shaders[NUM_OF_SHADERS]; //array of shaders
	GLuint uniforms[NUM_OF_UNIFORMS]; //no of uniform vars
};


