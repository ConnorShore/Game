#include "MainGame.h"



MainGame::MainGame() : _currentState(GameState::PLAY)
{
}

void MainGame::init()
{
	_window.createWindow("Platform Game", 1280, 720, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_INIT_EVERYTHING);

	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/test.png");

	_shader.init("Shaders/colorShader.vert", "Shaders/colorShader.frag");
	_shader.bindAttributes();
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

}

void MainGame::update()
{

}

void MainGame::render()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shader.start();
	_shader.getUniformLocations();
	_shader.loadTexture();

	for (int i = 0; i < _sprites.size(); i++) {
		_sprites[i]->draw();
	}

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
