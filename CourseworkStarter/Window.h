#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;

class Window
{
public:
	Window();
	~Window();
	void initialiseDisplay();
	void swapBuffer();
	void ClearDisplay(float r, float g, float b, float a);

	float GetWidth();
	float GetHeight();


private:

	void returnError(std::string eString);
	SDL_Window* window; //holds pointer window
	SDL_GLContext context;
	float screenW;
	float screenH;


};

