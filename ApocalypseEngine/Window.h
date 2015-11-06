#pragma once

enum ViewType { VIEW_2D, VIEW_3D };

#include <string>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Window
{
public:
	Window();
	~Window();

	void createWindow(std::string title, int width, int height, float x, float y, int initGLStatus);
	void swapWindow();

	//getters
	int getWidth() { return _width; }
	int getHeight() { return _height; }
	SDL_Window* getSDLWindow() { return _window; }

	float getWindowX() { return _x; }
	float getWindowY() { return _y; }
	ViewType getViewType() { return _viewType; }

	void setViewType(ViewType type) { _viewType = type; }
	void setBackgroundColor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }

private:
	ViewType _viewType;
	SDL_Window* _window;

	int _width, _height;
	float _x, _y;

	bool _showGL;
};

