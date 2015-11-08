#pragma once

#include <ApocalypseEngine\Window.h>
#include <ApocalypseEngine\InputManager.h>
#include <ApocalypseEngine\Sprite.h>
#include <ApocalypseEngine\Camera2D.h>
#include <ApocalypseEngine\SpriteBatch.h>

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
	int _screenWidth, _screenHeight;

	GameState _currentState;
	Window _window;
	InputManager _inputManager;
	StaticShader _shader;
	Camera2D _camera;
	SpriteBatch _spriteBatch;

	void init();
	void input();
	void update();
	void render();
	void gameLoop();
	void cleanUp();
};