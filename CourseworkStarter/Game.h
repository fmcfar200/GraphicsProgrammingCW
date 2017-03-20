#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Window.h" 
#include "MeshManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Transform.h"
#include "View.h"
enum class State { PLAY, EXIT };

class Game
{
public:
	Game();
	~Game();

	void RunGame();

private:
	void initialiseSystems();
	void updateInput();
	void gLoop();
	void draw();

	Window gameDisplay;
	State gameState;

	MeshManager mesh1;
	MeshManager mesh2;

	View camera;

	float count = 0;
};

