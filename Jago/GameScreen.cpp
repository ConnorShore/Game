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

	_dirt = ResourceManager::getTexture("Textures/dirt.png");	//< Init box texturex

	for (int i = 0; i < NUM_BOXES; i++) {
		Box newBox;
		newBox.init(_world.get(), glm::vec2(xDist(randomGen), yDist(randomGen)), glm::vec2(size(randomGen), size(randomGen)), _dirt, false);
		_boxes.push_back(newBox);
	}

	_camera.init(_window->getWidth(), _window->getHeight());
	_camera.setScale(38.0f);

	_spriteBatch.init();

	_staticShader.init("Shaders/colorShader.vert", "Shaders/colorShader.frag");
	_staticShader.bindAttributes();

	_lightShader.init("Shaders/lightShader.vert", "Shaders/lightShader.frag");
	_lightShader.bindAttributes();

	_player.init(_world.get(), glm::vec2(0.0f, 15.0f), glm::vec2(1.0f, 1.8f), glm::vec2(1.0f, 1.8f));

	Torch* torch = new Torch;
	torch->init(glm::vec2(1.0f, -10.0f), 10.0f, Color(195, 150, 0, 120));
	_torches.push_back(torch);
}

void GameScreen::onExit()
{

}

void GameScreen::update()
{
	_camera.update();
	input();

	_player.update(_game->inputManager, _torches);

	for (Torch* t : _torches) {
		t->update();
	}

	_world->Step(1.0f / 60.0f, 6, 2);
}

void GameScreen::render()
{
	//Basic OpenGL setup
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	_staticShader.start();
	_staticShader.getUniformLocations();
	_staticShader.loadPMatrix(_camera.getCameraMatrix());
	_staticShader.loadTexture();

	_spriteBatch.begin(SortType::FRONT_TO_BACK);;

	for (auto& box : _boxes) {
		box.render(_spriteBatch);
	}

	_player.render(_spriteBatch);	//< Draw Player
	//torch.render(_spriteBatch);

	for (Torch* t : _torches) {
		t->render(_spriteBatch);
	}

	_spriteBatch.end();
	_spriteBatch.renderBatch();;

	_staticShader.stop();

	//Render Lights
	_lightShader.start();
	_lightShader.getUniformLocations();
	_lightShader.loadPMatrix(_camera.getCameraMatrix());
	_spriteBatch.begin();

	for (Torch* t : _torches) {
		t->getLight().render(_spriteBatch);
	}

	_spriteBatch.end();
	_spriteBatch.renderBatch();
	_staticShader.stop();
	_lightShader.stop();
}

void GameScreen::input()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		_game->onSDLEvent(evnt);
	}
}