#pragma once

#include <string>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Window
{
public:
	Window();
	~Window();

	void createWindow(std::string title, int width, int height, float x, float y);
	void swapWindow();

	//getters
	int getWidth() { return _width; }
	int getHeight() { return _height; }
	SDL_Window* getSDLWindow() { return _window; }

	float getWindowX() { return _x; }
	float getWindowY() { return _y; }

private:
	SDL_Window* _window;

	int _width, _height;
	float _x, _y;

	bool _showGL;
};

