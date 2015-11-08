#include "MainGame.h"

#include <ApocalypseEngine\ResourceManager.h>
#include <iostream>


MainGame::MainGame() : _currentState(GameState::PLAY), _screenWidth(1280), _screenHeight(720)
{
}

void MainGame::init()
{
	_window.createWindow("Platform Game", _screenWidth, _screenHeight, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_INIT_EVERYTHING);
	_camera.init(_screenWidth, _screenHeight);

	_shader.init("Shaders/colorShader.vert", "Shaders/colorShader.frag");
	_shader.bindAttributes();

	_spriteBatch.init();
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
	const int CAM_SPEED = 5.0f;

	if (_inputManager.isKeyDown(SDLK_w)) _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAM_SPEED));
	if (_inputManager.isKeyDown(SDLK_s)) _camera.setPosition(_camera.getPosition() - glm::vec2(0.0f, CAM_SPEED));
	if (_inputManager.isKeyDown(SDLK_d)) _camera.setPosition(_camera.getPosition() + glm::vec2(CAM_SPEED, 0.0f));
	if (_inputManager.isKeyDown(SDLK_a)) _camera.setPosition(_camera.getPosition() - glm::vec2(CAM_SPEED, 0.0f));

	if (_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = _inputManager.getMousePos();
		mouseCoords = _camera.convertToWorldCoords(mouseCoords);
		std::cout << mouseCoords.x << ", " << mouseCoords.y << std::endl;
	}
}

void MainGame::update()
{
	_camera.update();
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

	_spriteBatch.begin();
	
	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	_spriteBatch.addToBatch(glm::vec4(0.0f, 0.0f, 100.0f, 220.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 0.0f, ResourceManager::getTexture("Textures/Player/idle_right.png").id, color);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	_shader.stop();
	_window.swapWindow();
}

void MainGame::gameLoop()
{
	while (_currentState != GameState::EXIT) {
		input();
		update();
		render();
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
}