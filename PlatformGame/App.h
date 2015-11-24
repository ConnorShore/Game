#pragma once

#include "GameScreen.h"

#include <ApocalypseEngine\IMainGame.h>

class App : public IMainGame
{
public:
	App();
	~App();

	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;

private:
	std::unique_ptr<GameScreen> _gameScreen = nullptr;
};

