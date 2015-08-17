#include "MainGame.h"

#include <SDL\SDL.h>
#include <iostream>


MainGame::MainGame() : _screenWidth(1280), _screenHeight(720), _vaoID(0)
{
}

void MainGame::initSystems()
{
	_currentState = GameState::PLAY;
	SDL_Init(SDL_INIT_EVERYTHING);

	_window.createWindow("Game", _screenWidth, _screenHeight, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	_camera.init(glm::vec3(0.0f, 0.0f, 4.0f), _screenWidth, _screenHeight, 60.0f, 5.0f, 0.0005f);


	_test->init("Models/box.obj", "Textures/default.png");
	_assets.push_back(_test);
}

void MainGame::initShaders()
{
	_staticShader.init("Shaders/staticShader.vert", "Shaders/staticShader.frag");
	_staticShader.bindAttributes();
}

void MainGame::initLights()
{
	_light.init(glm::vec3(2.0f,0.0f,5.0f), glm::vec3(1.0f, 1.0f, 1.0f));
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
			_camera.setMousePos(glm::ivec2(evnt.motion.x, evnt.motion.y));
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.keyPressed(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.keyReleased(evnt.button.button);
			break;
		}
	}

	//Move camera
	if (_inputManager.isKeyDown(SDLK_w)) { _camera.setPosition(_camera.getPosition() + _camera.getDirection() * _timer.getDeltaTime() * _camera.getCamSpeed()); }
	if (_inputManager.isKeyDown(SDLK_s)) { _camera.setPosition(_camera.getPosition() - _camera.getDirection() * _timer.getDeltaTime() * _camera.getCamSpeed()); }
	if (_inputManager.isKeyDown(SDLK_a)) { _camera.setPosition(_camera.getPosition() - _camera.getRight() * _timer.getDeltaTime() * _camera.getCamSpeed()); }
	if (_inputManager.isKeyDown(SDLK_d)) { _camera.setPosition(_camera.getPosition() + _camera.getRight() * _timer.getDeltaTime() * _camera.getCamSpeed()); }

	if (_inputManager.isKeyDown(SDLK_ESCAPE)) {
		if (showCursor != 1) {
			_camera.setMouseLook(false);
			showCursor = 1;
			SDL_ShowCursor(showCursor);
		}
	}

	if (_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
		if (showCursor != 0) {
			_camera.setMousePos(glm::ivec2(_screenWidth / 2, _screenHeight / 2));
			_camera.setMouseLook(true);
			showCursor = 0;
			SDL_ShowCursor(showCursor);
		}
	}
}

void MainGame::bindUniforms()
{
	_staticShader.getUniformLocations();
}

void MainGame::update()
{
	_camera.update();
	//_test->setRotation(_test->getRotation() + 1.0f, _test->getRotationAxis());
	//_light.setPosition(_light.getPosition() + glm::vec3(0.0f,0.0f,-0.1f));
}

void MainGame::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_staticShader.start();

	bindUniforms();

	_staticShader.loadLight(_light);

	_camera.createViewMatrix();
	_staticShader.loadViewMatrix(_camera);
	_projectionMatrix = _camera.createProjectionMatrix();
	_staticShader.loadProjectionMatrix(_projectionMatrix);

	for (int i = 0; i < _assets.size(); i++)
		_assets[i]->bind();

	_staticShader.loadTexture();

	for (int i = 0; i < _assets.size(); i++) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _assets[0]->getTexture().id);
	}

	for (int i = 0; i < _assets.size(); i++) {
		static glm::mat4 modelMat;
		modelMat = _assets[i]->createModelMatrix();
		_staticShader.loadModelMatrix(modelMat);
		_assets[i]->render();
	}

	for (int i = 0; i < _assets.size(); i++)
		_assets[i]->unbind();

	glBindTexture(GL_TEXTURE_2D, 0);

	_window.swapWindow();
}

void MainGame::gameLoop()
{
	while (_currentState != GameState::EXIT) {
		_timer.FpsLimitInit();
		_timer.calcDeltaTime();

		input();
		update();
		render();

		_timer.CalculateFPS(false);
		_timer.LimitFPS(60);
	}

	cleanUp();
}

void MainGame::cleanUp()
{
	glDeleteVertexArrays(1, &_vaoID);

	_staticShader.cleanUp();

	SDL_Quit();
	exit(0);
}

void MainGame::run()
{
	initSystems();
	initShaders();
	initLights();
	gameLoop();
}

MainGame::~MainGame()
{
}