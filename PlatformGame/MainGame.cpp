#include "MainGame.h"

#include <ApocalypseEngine\ResourceManager.h>
#include <iostream>

MainGame::MainGame() : _currentState(GameState::PLAY), _screenWidth(1280), _screenHeight(720), _player(nullptr)
{
}

void MainGame::initShaders()
{
	_shader.init("Shaders/colorShader.vert", "Shaders/colorShader.frag");
	_shader.bindAttributes();
}

void MainGame::initLevels()
{
	_levels.push_back(new Level("Levels/level1.txt"));
	_currentLevel = 0;

	_player = new Player;
	_player->init(_levels[_currentLevel]->getStartPlayerPos());
	_friendlies.push_back(_player);
}

void MainGame::init()
{
	_window.createWindow("Platform Game", _screenWidth, _screenHeight, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_INIT_EVERYTHING);
	_camera.init(_screenWidth, _screenHeight);

	_friendlySpriteBatch.init();

	initShaders();
	initLevels();
}

void MainGame::input()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_currentState = GameState::EXIT;
			break;

		case SDL_KEYDOWN:
			_inputManager.keyPressed(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.keyReleased(evnt.key.keysym.sym);
			break;

		case SDL_MOUSEMOTION:
			_inputManager.setMousePos(glm::vec2(evnt.motion.x, evnt.motion.y));
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.keyPressed(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.keyReleased(evnt.button.button);
			break;
		}
	}

	//Keybindings

	_player->input(_inputManager);
}

void MainGame::update()
{
	_camera.setPosition(_player->getPosition());
	_camera.update();

	for (int i = 0; i < _agents.size(); i++)
		_agents[i]->update();
}

void MainGame::render()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shader.start();
	_shader.getUniformLocations();

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	_shader.loadPMatrix(cameraMatrix);

	_shader.loadTexture();

	_friendlySpriteBatch.begin();

	_levels[_currentLevel]->render();

	//Draw Friendies
	for (int i = 0; i < _friendlies.size(); i++)
		_friendlies[i]->render(_friendlySpriteBatch);
	
	_friendlySpriteBatch.end();
	_friendlySpriteBatch.renderBatch();

	_shader.stop();
	_window.swapWindow();
}

void MainGame::gameLoop()
{
	_timer.TimeInit();

	while (_currentState != GameState::EXIT) {
		_timer.FpsLimitInit();
		_timer.calcDeltaTime();

		input();
		update();
		render();

		_timer.CalculateFPS(false);
		_timer.LimitFPS(60.0f);
	}
}

void MainGame::run() {
	init();
	gameLoop();
	cleanUp();
}

void MainGame::cleanUp()
{
	_shader.cleanUp();

	SDL_Quit();
	exit(0);
}

MainGame::~MainGame()
{
	for (int i = 0; i < _agents.size(); i++)
		delete _agents[i];

	for (int i = 0; i < _friendlies.size(); i++)
		delete _friendlies[i];

	for (int i = 0; i < _enemies.size(); i++)
		delete _enemies[i];

	for (int i = 0; i < _bullets.size(); i++)
		delete _bullets[i];

	for (int i = 0; i < _levels.size(); i++)
		delete _levels[i];
}