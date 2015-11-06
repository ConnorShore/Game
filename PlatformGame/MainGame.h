#pragma once

#include <ApocalypseEngine\Window.h>
#include <ApocalypseEngine\InputManager.h>
#include <ApocalypseEngine\Sprite.h>

#include "StaticShader.h"

#include <vector>

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	GameState _currentState;
	Window _window;
	InputManager _inputManager;
	StaticShader _shader;

	std::vector<Sprite*> _sprites;

	void init();
	void input();
	void update();
	void render();
	void gameLoop();
	void cleanUp();
};