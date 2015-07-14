#include "MainGame.h"
#include "Error.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL\SDL.h>
#include <fstream>
#include <iostream>


MainGame::MainGame() : _screenWidth(1280), _screenHeight(720), _vaoID(0)
{

}

void MainGame::initSystems()
{
	_currentState = GameState::PLAY;
	SDL_Init(SDL_INIT_EVERYTHING);

	_window.createWindow("Game", _screenWidth, _screenHeight, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	_camera.init(glm::vec3(0.0f, 0.0f, 4.0f), _screenWidth, _screenHeight, 70.0f, 0.005f);

	_player.init("Models/monkey.obj", "Textures/default.png", glm::vec3(-2.0f, 0.0f, -4.0f), 1.0f);
	_assets.push_back(_player);

	_test.init("Models/monkey.obj", "Textures/default.png", glm::vec3(2.0f, 0.0f, -4.0f), 1.0f);
	_assets.push_back(_test);
}

void MainGame::initShaders()
{
	_staticProgram = Loader::loadShaders("Shaders/colorShader.vert", "Shaders/colorShader.frag");

	glBindAttribLocation(_staticProgram, 0, "vertexPosition");
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
			_camera.setMousePos(glm::vec2(evnt.motion.x, evnt.motion.y));
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.keyPressed(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.keyReleased(evnt.button.button);
			break;
		}
	}

	if (_inputManager.isKeyDown(SDLK_w)) { _player.setPosition(_player.getPosition() + _camera.getDirection() * _timer.getDeltaTime() * _camera.getCamSpeed()); }
	if (_inputManager.isKeyDown(SDLK_w)) { _camera.setPosition(_camera.getPosition() + _camera.getDirection() * _timer.getDeltaTime() * _camera.getCamSpeed()); }
	if (_inputManager.isKeyDown(SDLK_s)) { _camera.setPosition(_camera.getPosition() - _camera.getDirection() * _timer.getDeltaTime() * _camera.getCamSpeed()); }
	if (_inputManager.isKeyDown(SDLK_a)) { _camera.setPosition(_camera.getPosition() - _camera.getRight() * _timer.getDeltaTime() * _camera.getCamSpeed()); }
	if (_inputManager.isKeyDown(SDLK_d)) { _camera.setPosition(_camera.getPosition() + _camera.getRight() * _timer.getDeltaTime() * _camera.getCamSpeed()); }

	if (_inputManager.isKeyDown(SDLK_ESCAPE)) { SDL_SetRelativeMouseMode(SDL_FALSE); }
}

void MainGame::bindUniforms()
{
	GLuint pLocation = glGetUniformLocation(_staticProgram, "P");
	glm::mat4 camMatrix = _camera.getMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(camMatrix[0][0]));

	GLuint modelLocation = glGetUniformLocation(_staticProgram, "model");
	for (int i = 0; i < _assets.size(); i++) {
		glm::mat4 model;
		model = glm::translate(_assets[i].getModelMatrix(), _player.getPosition());
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		std::cout << _player.getPosition().z << std::endl;

		_assets[i].render();
	}

	//glm::mat4 playerModel = glm::translate(_player.getModelMatrix(), _player.getPosition());
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(playerModel));

	GLuint texLoc = glGetUniformLocation(_staticProgram, "testTex");
	glUniform1i(texLoc, 0);
}

void MainGame::update()
{
	_camera.update();
}

void MainGame::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(_staticProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _player.getTexture().id);

	for (int i = 0; i < _assets.size(); i++) {
		_assets[i].bind();
	}

	for (int i = 0; i < _assets.size(); i++) {
		_assets[i].render();
	}

	bindUniforms();

	for (int i = 0; i < _assets.size(); i++) {
		_assets[i].unbind();
	}

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
	// Cleanup VBO and shader
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_uvBuffer);
	glDeleteProgram(_staticProgram);
	glDeleteVertexArrays(1, &_vaoID);

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