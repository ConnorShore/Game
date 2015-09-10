#include "Window.h"
#include "Error.h"
#include <iostream>

Window::Window() : _window(nullptr), _showGL(false)
{

}

void Window::createWindow(std::string title, int width, int height, float x, float y)
{
	_width = width;
	_height = height;
	_x = x;
	_y = y;

	_window = SDL_CreateWindow(title.c_str(), _x, _y, _width, _height, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {
		fatalError("Failed to create SDL Window");
	}

	SDL_GLContext glContext;
	glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("Failed to create GL Context");
	}

	glewExperimental = GL_TRUE;

	GLenum error;
	error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Failed to initialize glew");
	}

	glViewport(0, 0, _width, _height);

	glClearColor(0.05f, 0.0f, 0.25f, 1.0f);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::swapWindow()
{
	SDL_GL_SwapWindow(_window);
}

Window::~Window()
{
}