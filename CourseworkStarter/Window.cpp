#include "Window.h"



Window::Window()
{
	window = nullptr;
	screenH = 768.0f;
	screenW = 1024.0f;

}


Window::~Window()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::initialiseDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //init everything


	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenW, (int)screenH, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window); //create gl context

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont draw faces that are not pointing at the camera


	GLenum error = glewInit();// init glew

	if (window == nullptr)
	{
		returnError("window failed to create");
	}

	if (context == nullptr)
	{
		returnError("SDL_GL context failed to create");
	}

	if (error != GLEW_OK)
	{
		returnError("GLEW failed to initialise");
	}

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f); //sets background colour
}

void Window::swapBuffer()
{
	SDL_GL_SwapWindow(window);
}

void Window::ClearDisplay(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

float Window::GetWidth()
{
	return screenW;
}

float Window::GetHeight()
{
	return screenH;
}

void Window::returnError(std::string eString)
{
	std::cout << eString << std::endl;
	std::cout << "press any  key to quit...";
	int in;
	std::cin >> in;
	SDL_Quit();
}
