#pragma once

#include <vector>

class IMainGame;
class IGameScreen;

class ScreenList
{
public:
	ScreenList(IMainGame* game);
	~ScreenList();

	IGameScreen* moveNext();
	IGameScreen* movePrevious();
	IGameScreen* getCurrent();

	void setScreen(int nextScreen);
	void addScreen(IGameScreen* newScreen);

	void destroy();

protected:
	IMainGame* _game;
	std::vector<IGameScreen*> _screens;
	int _currentScreenIndex = -1;
};

