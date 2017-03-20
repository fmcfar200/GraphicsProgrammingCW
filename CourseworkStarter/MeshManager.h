#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include <vector>
#include "obj_loader.h"

class VertexManager
{
public:
	VertexManager(const glm::vec3& pos, const glm::vec2& textureCoord)
	{
		this->position = pos;
		this->textureCoord = textureCoord;
		this->norm = norm;

	}

	glm::vec3 position;
	glm::vec2 textureCoord;
	glm::vec3 norm;

	glm::vec3* GetPosition() { return &position; }
	glm::vec2* GetTextureCoord() { return &textureCoord; }
	glm::vec3* GetNorm() { return &norm; }

protected:
private:
	

};

class MeshManager
{
public:
	MeshManager();
	~MeshManager();
	void DrawMesh();

	void initialise(VertexManager* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void loadModelFromFile(const std::string& filename);
	void initialiseModel(const IndexedModel& model);


private:

	enum
	{
		POSITION_VERTEXBUFFER,
		TEXTURECOORDS_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFER
	};

	GLuint VAO;
	GLuint VABs[NUM_BUFFER];//creates our areray of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to draw


};

