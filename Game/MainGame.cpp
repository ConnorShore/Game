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
	_camera.init(glm::vec3(0.0f, 0.0f, 4.0f), _screenWidth, _screenHeight, 70.0f, 0.005f, 0.0005f);


	_test->init("Models/monkey.obj", "Textures/default.png", 1.0f);
	_assets.push_back(_test);
}

void MainGame::initShaders()
{
	_staticShader.init("Shaders/staticShader.vert", "Shaders/staticShader.frag");
	_staticShader.bindAttributes();
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
	////Binding transformation matrix
	//GLuint pLocation = glGetUniformLocation(_staticShader.getProgram(), "transformMatrix");
	//glm::mat4 camMatrix = _camera.getMatrix();
	//glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(camMatrix[0][0]));

	_staticShader.getUniformLocations();

	////binding model matrix for each asset (Not working for moving player)
	//GLuint modelLocation = glGetUniformLocation(_staticShader.getProgram(), "model");
	//for (unsigned int i = 0; i < _assets.size(); i++) {
	//	glm::mat4 model;
	//	model = glm::translate(_assets[i]->getModelMatrix(), _assets[i]->getPosition());
	//	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	//	_assets[i]->render();
	//}

	//GLuint texLoc = glGetUniformLocation(_staticProgram, "myTexture");
	//glUniform1i(texLoc, 0);

}

void MainGame::update()
{
	_camera.update();
}

void MainGame::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_staticShader.start();

	bindUniforms();

	for (int i = 0; i < _assets.size(); i++)
		_assets[i]->bind();

	_staticShader.loadTexture();

	for (int i = 0; i < _assets.size(); i++) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _assets[0]->getTexture().id);
	}

	_staticShader.loadCameraMatrix(_camera);

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

		_timer.CalculateFPS(true);
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
	gameLoop();
}

MainGame::~MainGame()
{
}