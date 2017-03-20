#include "ShaderManager.h"
#include <iostream>
#include <fstream>

ShaderManager::ShaderManager(const std::string & filename)
{
	shaderProg = glCreateProgram();
	shaders[0] = CreateShader(LoadShaderFromFile(filename+"shader.vert"), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadShaderFromFile(filename+"shader.frag"), GL_FRAGMENT_SHADER);

	for (int i = 0; i < NUM_OF_SHADERS; i++)
	{
		glAttachShader(shaderProg, shaders[i]);
	}

	glBindAttribLocation(shaderProg, 0, "position");
	glBindAttribLocation(shaderProg, 1, "textureCoord");

	glLinkProgram(shaderProg); //creates executables that will run on the gpu shader
	CheckShaderError(shaderProg, GL_LINK_STATUS, true, "Error: Shader shaderProg linking failed"); //checks for errors

	glValidateProgram(shaderProg); //checks entire program is valid
	CheckShaderError(shaderProg, GL_VALIDATE_STATUS, true, "Error: Shader program is not valid");
	
	uniforms[TRANSFORM_UNIF] = glGetUniformLocation(shaderProg, "trans");

}

ShaderManager::~ShaderManager()
{
	for (int i = 0; i < NUM_OF_SHADERS; i++)
	{
		glDetachShader(shaderProg, shaders[i]); //detache shader from prog
		glDeleteShader(shaders[i]);


	}

	glDeleteProgram(shaderProg);

}


void ShaderManager::BindShader()
{
	glUseProgram(shaderProg);
}

std::string ShaderManager::LoadShaderFromFile(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void ShaderManager::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

GLuint ShaderManager::CreateShader(const std::string & text, unsigned int type)
{
	GLuint shader = glCreateShader(type); //create shader based on specified type

	if (shader == 0) //if == 0 shader no created
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return shader;
}

void ShaderManager::Update(const Transform & trans, const View & camera)
{
	glm::mat4 modelMat = camera.GetViewProjectionMatrix() * trans.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_UNIF], 1, GLU_FALSE, &modelMat[0][0]);

}


