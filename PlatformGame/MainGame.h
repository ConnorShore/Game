#pragma once

#include <vector>

#include <ApocalypseEngine\Window.h>
#include <ApocalypseEngine\InputManager.h>
#include <ApocalypseEngine\Sprite.h>
#include <ApocalypseEngine\Camera2D.h>
#include <ApocalypseEngine\SpriteBatch.h>
#include <ApocalypseEngine\Timing.h>

#include "StaticShader.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Level.h"


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
	SpriteBatch _friendlySpriteBatch;
	Timing _timer;
	Player* _player;

	std::vector<Agent*> _agents;
	std::vector<Friendly*> _friendlies;
	std::vector<Enemy*> _enemies;
	std::vector<Bullet*> _bullets;
	std::vector<Level*> _levels;

	int _currentLevel;

	void initShaders();
	void initLevels();
	void init();
	void input();
	void update();
	void render();
	void gameLoop();
	void cleanUp();
};