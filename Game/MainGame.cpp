#include "MainGame.h"

#include <ApocalypseEngine\Collision.h>
#include <SDL\SDL.h>
#include <iostream>


MainGame::MainGame() : _screenWidth(1280), _screenHeight(720), _vaoID(0)
{
}

void MainGame::initSystems()
{
	_currentState = GameState::PLAY;

	_window.createWindow(VERSION, _screenWidth, _screenHeight, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_INIT_EVERYTHING, false);

	_camera.init(glm::vec3(_player->getPosition().x, _player->getPosition().y - 2.0f, _camera.getFollowDist()), _screenWidth, _screenHeight, 80.0f, 5.0f, 0.0005f);
	_camera.setMouseLook(false);
	_camera.setFollowDist(25.0f);

	_player->init("Models/human_model.obj", "Textures/default.png");
	_assets.push_back(_player);
	_actors.push_back(_player);
	_player->initPlayer();

	_monkey->init("Models/human_model.obj", "Textures/default.png");
	_assets.push_back(_monkey);
	_actors.push_back(_monkey);
	_monkey->setBounds(_monkey->createRectangleBoundsToModel());
	_monkey->addBounds(_monkey->getBounds(), false);

	_monkey2->init("Models/human_model.obj", "Textures/default.png");
	_assets.push_back(_monkey2);
	_actors.push_back(_monkey2);
	_monkey2->setBounds(_monkey2->createRectangleBoundsToModel());
	_monkey2->addBounds(_monkey2->getBounds(), false);
}

void MainGame::initShaders()
{
	_staticShader.init("Shaders/staticShader.vert", "Shaders/staticShader.frag");
	_staticShader.bindAttributes();
}

void MainGame::initLights()
{
	_light.init(glm::vec3(2.0f, 8.0f, 6.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.09f, 0.0032f));
	_sun.init(glm::vec3(5.0f, 75.0f, 25.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.00002f, 0.000008f));
}

void MainGame::updateLights()
{
	_lights.push_back(_light);
	_lights.push_back(_sun);
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

	if (_inputManager.isKeyDown(SDLK_w)) {
		_player->setPosition(_player->getPosition() + glm::vec3(0.0f, 1.0f, 0.0f) * _timer.getDeltaTime() * _player->getWalkSpeed());
	}

	if (_inputManager.isKeyDown(SDLK_s)) {
		_player->setPosition(_player->getPosition() - glm::vec3(0.0f, 1.0f, 0.0f) * _timer.getDeltaTime() * _player->getWalkSpeed());
	}

	if (_inputManager.isKeyDown(SDLK_a)) { 
		_player->setPosition(_player->getPosition() - glm::vec3(1.0f, 0.0f, 0.0f) * _timer.getDeltaTime() * _player->getWalkSpeed()); 
	}

	if (_inputManager.isKeyDown(SDLK_d)) { 
		_player->setPosition(_player->getPosition() + glm::vec3(1.0f, 0.0f, 0.0f) * _timer.getDeltaTime() * _player->getWalkSpeed());
	}

	if (_inputManager.isKeyDown(SDLK_F1))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (_inputManager.isKeyDown(SDLK_F2))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void MainGame::update()
{
	_camera.update();
	_camera.setPosition(_player->getPosition() + glm::vec3(0.0f, -2.25f, _camera.getFollowDist()));

	for (int i = 0; i < _assets.size(); i++) _assets[i]->update();

	for (int i = 0; i < _actors.size(); i++) {
		if(_player != _actors[i])
			Collision::actAABBCollision(_player, _actors[i]);
	}

	//_physics.updateCollision(_actors);

	updateLights();
}

void MainGame::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_staticShader.start();

	_staticShader.getUniformLocations();

	_staticShader.loadLights(_lights);

	_camera.createViewMatrix();
	_staticShader.loadViewMatrix(_camera);
	_projectionMatrix = _camera.createProjectionMatrix();

	_staticShader.loadProjectionMatrix(_projectionMatrix);

	_staticShader.loadTexture();

	for (int i = 0; i < _assets.size(); i++) {
		static glm::mat4 modelMat;
		modelMat = _assets[i]->createModelMatrix();
		_staticShader.loadModelMatrix(modelMat);

		_assets[i]->render();

		//Clear and reload light vector and memory
		_lights.clear();
		std::vector<BaseLight>(_lights).swap(_lights);
	}

	_staticShader.stop();

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
	cleanUp();
}

MainGame::~MainGame()
{
}