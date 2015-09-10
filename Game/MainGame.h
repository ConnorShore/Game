#pragma once

#include "AE/Window.h"
#include "AE/StaticShader.h"
#include "AE/Camera.h"
#include "AE/GLTexture.h"
#include "AE/Asset.h"
#include "AE/InputManager.h"
#include "AE/Timing.h"
#include "AE/Light.h"
#include "AE/Item.h"

#include "Player.h"

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	Window _window;
	GameState _currentState;
	Camera _camera;
	InputManager _inputManager;
	Timing _timer;
	StaticShader _staticShader;

	Light _light;
	Light _sun;

	Player* _player = new Player(glm::vec3(0.0f, 1.0f, 0.0f));

	Item* _test = new Item("Test", glm::vec3(2.0f, 1.0f, -4.0f), false);
	Asset* _test1 = new Asset(glm::vec3(-2.0f, 1.0f, -2.0f));
	Asset* _ground = new Asset(glm::vec3(0.0f,0.0f,0.0f));

	GLTexture _standard;
	GLTexture _standard1;

	std::vector<Vertex> _vertices;
	std::vector<Asset*> _assets;
	std::vector<Light> _lights;

	GLuint _vaoID;

	glm::mat4 _projectionMatrix;

	int _screenWidth, _screenHeight;
	int showCursor = 0;

	float _playerSpeed = 0.25f;

	void initSystems();
	void initShaders();
	void initLights();
	void updateLights();
	void input();
	void update();
	void render();
	void bindUniforms();
	void gameLoop();
	void cleanUp();

	const std::string VERSION = "v0.1.1";
};