#include "GameScreen.h"
#include <ApocalypseEngine\IMainGame.h>
#include <SDL\SDL.h>


GameScreen::GameScreen()
{
}

GameScreen::~GameScreen()
{
}

int GameScreen::getNextScreenIndex() const
{
	return NULL_SCREEN_INDEX;
}

int GameScreen::getPreviousScreenIndex() const
{
	return NULL_SCREEN_INDEX;
}

void GameScreen::build()
{
}

void GameScreen::destroy()
{
}

void GameScreen::onEntry()
{
}

void GameScreen::onExit()
{
}

void GameScreen::update()
{
	input();
}

void GameScreen::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.0f, 0.25f, 1.0f);
}

void GameScreen::input()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		_game->onSDLEvent(evnt);
	}
}