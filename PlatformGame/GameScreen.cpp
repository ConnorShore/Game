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

	//Init Camera
	_camera.init(_window->getWidth(), _window->getHeight());
	_camera.setScale(32.0f);	//< 1 meter = 32 pixels

	//Tile test
	//GLTexture texture = ResourceManager::getTexture("Textures/test.png");
	//Tile tile;
	//tile.init(_world.get(), glm::vec2(0.0f, 0.0f), glm::vec2(10.0f, 10.0f), texture);
	//_tiles.push_back(tile);

	//Init Sprite Batches
	_spriteBatch.init();

	//Init Shaders
	_shader.init("Shaders/colorShader.vert", "Shaders/colorShader.frag");
	_shader.bindAttributes();

	//Init Player
	_player.init(_world.get(), glm::vec2(0.0f, 15.0f), glm::vec2(1.0f, 1.8f), glm::vec2(2.0f,2.0f));
}

void GameScreen::onExit()
{
}

void GameScreen::update()
{
	_camera.update();
	input(_game->inputManager);

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
	for (auto& bullet : _bullets) {
		bullet.render(_spriteBatch);
	}

	_player.render(_spriteBatch); //< Draw the player

	//Render spritebatch
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	//Unuse color shader
	_shader.stop();

	//Begin spritebatch
	_spriteBatch.begin();

	//Render spritebatch
	_spriteBatch.end();
	_spriteBatch.renderBatch();
}

void GameScreen::input(InputManager inputManager)
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		_game->onSDLEvent(evnt);
	}

	//Bullet test
	if (inputManager.isKeyDown(SDLK_LSHIFT)) {
		_bullets.emplace_back(_world.get(), glm::vec2(_player.getPosition().x + 1.0f, _player.getPosition().y), glm::vec2(1.0f, 0.0f), 20.0f);
	}
}