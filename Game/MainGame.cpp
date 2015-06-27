#include "MainGame.h"
#include "Error.h"

#include <glm/gtc/matrix_transform.hpp>
#include <SDL\SDL.h>
#include <fstream>
#include <iostream>

using namespace std;


MainGame::MainGame() : _screenWidth(1280), _screenHeight(720), _vaoID(0)
{
	//_camera.init(_screenWidth, _screenHeight);
}

void MainGame::initSystems()
{
	_currentState = GameState::PLAY;
	SDL_Init(SDL_INIT_EVERYTHING);

	_window.createWindow("Game", _screenWidth, _screenHeight, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	_player.init("Models/monkey.obj", "Textures/default.png", glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
	glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.0, 4.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 projection = glm::perspective(70.0f, 1.0f*_screenWidth / _screenHeight, 0.1f, 10.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	camMatrix = projection * view * model; // Remember, matrix multiplication is the other way around
}

void MainGame::initShaders()
{
	_programID = Loader::loadShaders("Shaders/colorShader.vert", "Shaders/colorShader.frag");
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
				switch (evnt.key.keysym.sym) {

				}
				break;
		}
	}
}

void MainGame::bindUniforms()
{
	GLuint pLocation = glGetUniformLocation(_programID, "P");
	//glm::mat4 camMatrix = _camera.getMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(camMatrix[0][0]));

	GLuint texLoc = glGetUniformLocation(_programID, "testTex");
	glUniform1i(texLoc, 0);
}

void MainGame::update()
{
	//_camera.update();
}

void MainGame::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(_programID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _player.getTexture().id);

	_player.bind();

	bindUniforms();

	_player.render();

	_player.unbind();

	glBindTexture(GL_TEXTURE_2D, 0);

	_window.swapWindow();
}

void MainGame::gameLoop()
{
	while (_currentState != GameState::EXIT) {
		input();
		update();
		render();
	}
	
	cleanUp();
}

void MainGame::cleanUp()
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_uvBuffer);
	glDeleteProgram(_programID);
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
