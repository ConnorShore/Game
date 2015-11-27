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
	b2Vec2 gravity(0.0f, -9.81f);
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
	const int NUM_BOXES = 40;

	for (int i = 0; i < NUM_BOXES; i++) {
		Box newBox;
		newBox.init(_world.get(), glm::vec2(xDist(randomGen), yDist(randomGen)), glm::vec2(size(randomGen), size(randomGen)));
		_boxes.push_back(newBox);
	}

	_boxTex = ResourceManager::getTexture("Textures/bullet.png");

	_camera.init(_window->getWidth(), _window->getHeight());
	_camera.setScale(32.0f);	//< 1 meter = 32 pixels

	_spriteBatch.init();

	_shader.init("Shaders/colorShader.vert", "Shaders/colorShader.frag");
	_shader.bindAttributes();
}

void GameScreen::onExit()
{
}

void GameScreen::update()
{
	_camera.update();
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
		glm::vec4 destRect;
		destRect.x = box.getBody()->GetPosition().x;
		destRect.y = box.getBody()->GetPosition().y;
		destRect.z = box.getDimension().x;
		destRect.w = box.getDimension().y;

		Color color;
		color.r = 255;
		color.g = 255;
		color.b = 255;
		color.a = 255;

		_spriteBatch.addToBatch(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 0.0f, _boxTex.id, color, box.getBody()->GetAngle());
	}

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