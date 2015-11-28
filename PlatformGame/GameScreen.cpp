#include "GameScreen.h"

#include <ApocalypseEngine\ResourceManager.h>
#include <ApocalypseEngine\IMainGame.h>

#include <random>
#include <SDL\SDL.h>


GameScreen::GameScreen(Window* window) : _window(window)
{
}

GameScreen::~GameScreen()
{
}

int GameScreen::getNextScreenIndex() const
{
	return NULL_SCREEN_INDEX;
}

int GameScreen::getPreviousScreenIndex() const
{
	return NULL_SCREEN_INDEX;
}

void GameScreen::build()
{
}

void GameScreen::destroy()
{
}

void GameScreen::onEntry()
{
	//Create the world
	b2Vec2 gravity(0.0f, -25.0f);
	_world = std::make_unique<b2World>(gravity);

	//Make the ground
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -20.0f);
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);

	//Make ground fixture (hit box);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);	//< Density is 0 because it is static

	//Create boxes
	std::mt19937 randomGen;
	std::uniform_real_distribution<float> xDist(-10.0f, 10.0f);
	std::uniform_real_distribution<float> yDist(-10.0f, 15.0f);
	std::uniform_real_distribution<float> size(1.0f, 2.0f);

	const int NUM_BOXES = 45;

	_boxTex = ResourceManager::getTexture("Textures/bullet.png");	//< Init box texturex

	for (int i = 0; i < NUM_BOXES; i++) {
		Box newBox;
		newBox.init(_world.get(), glm::vec2(xDist(randomGen), yDist(randomGen)), glm::vec2(size(randomGen), size(randomGen)), _boxTex, false);
		_boxes.push_back(newBox);
	}

	//Init Camera
	_camera.init(_window->getWidth(), _window->getHeight());
	_camera.setScale(32.0f);	//< 1 meter = 32 pixels

	//Init Sprite Batches
	_spriteBatch.init();

	//Init Shaders
	_shader.init("Shaders/colorShader.vert", "Shaders/colorShader.frag");
	_shader.bindAttributes();

	//Init Player
	_player.init(_world.get(), glm::vec2(0.0f, 30.0f), glm::vec2(1.0f, 2.0f));
}

void GameScreen::onExit()
{
}

void GameScreen::update()
{
	_camera.update();
	_player.update(_game->inputManager);
	input();

	//Update physics simulations
	_world->Step(1 / 60.0f, 6, 2);
}

void GameScreen::render()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.0f, 0.25f, 1.0f);

	_shader.start();
	_shader.getUniformLocations();
	_shader.loadPMatrix(_camera.getCameraMatrix());
	_shader.loadTexture();

	_spriteBatch.begin();

	//Draw boxes
	for (auto& box : _boxes) {
		box.render(_spriteBatch);
	}

	_player.render(_spriteBatch); //< Draw the player

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	_shader.stop();
}

void GameScreen::input()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		_game->onSDLEvent(evnt);
	}
}