#pragma once

#include "Window.h"
#include "InputManager.h"
#include <memory>

class ScreenList;
class IGameScreen;

class IMainGame
{
public:
	IMainGame();
	virtual ~IMainGame();

	void run();
	void exitGame();

	void onSDLEvent(SDL_Event& evnt);

	virtual void onInit() = 0;
	virtual void addScreens() = 0;
	virtual void onExit() = 0;

	float getFPS() const { return _fps; }
	
	InputManager inputManager;

protected:
	std::unique_ptr<ScreenList> _screenList = nullptr;
	IGameScreen* _currentScreen = nullptr;
	Window _window;
	bool _isRunning = false;
	float _fps = 0;

	bool init();
	bool initSystems();

	virtual void update();
	virtual void render();
};

