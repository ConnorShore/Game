#include "App.h"
#include "ApocalypseEngine\ScreenList.h"


App::App()
{
}


App::~App()
{
}

void App::onInit()
{
}

void App::addScreens()
{
	_gameScreen = std::make_unique<GameScreen>(&_window);
	_screenList->addScreen(_gameScreen.get());
	_screenList->setScreen(_gameScreen->getScreenIndex());
}

void App::onExit()
{
}
