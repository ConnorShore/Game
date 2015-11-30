#include "GameScreen.h"

#include <ApocalypseEngine\ResourceManager.h>
#include <ApocalypseEngine\IMainGame.h>
#include <ApocalypseEngine\Light2D.h>

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

	const int NUM_BOXES = 10;

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

	_lightShader.init("Shaders/lightShader.vert", "Shaders/lightShader.frag");
	_lightShader.bindAttributes();

	//Init Player
	_player.init(_world.get(), glm::vec2(0.0f, 30.0f), glm::vec2(1.0f, 1.8f), glm::vec2(2.0f,2.0f));
}

void GameScreen::onExit()
{
}

void GameScreen::update()
{
	_camera.update();
	input();

	_player.update(_game->inputManager);

	//Update physics simulations
	_world->Step(1 / 60.0f, 6, 2);
}

void GameScreen::render()
{
	//Basic OpenGL setup
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.0f, 0.25f, 1.0f);

	//Load color shader
	_shader.start();
	_shader.getUniformLocations();
	_shader.loadPMatrix(_camera.getCameraMatrix());
	_shader.loadTexture();

	//Begin spritebatch
	_spriteBatch.begin();

	//Draw boxes
	for (auto& box : _boxes) {
		box.render(_spriteBatch);
	}

	_player.render(_spriteBatch); //< Draw the player

	//Render spritebatch
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	//Unuse color shader
	_shader.stop();

	//render test lights
	Light2D playerLight;
	playerLight.color = Color(255, 255, 255, 170);
	playerLight.position = _player.getPosition();
	playerLight.size = 10.0f;

	//Load light shader
	_lightShader.start();
	_lightShader.getUniformLocations();
	_lightShader.loadPMatrix(_camera.getCameraMatrix());

	//Begin spritebatch
	_spriteBatch.begin();

	playerLight.render(_spriteBatch);	//< Render light

	//Render spritebatch
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	//Unuse light shader
	_lightShader.stop();
}

void GameScreen::input()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		_game->onSDLEvent(evnt);
	}
}