#pragma once

#include <ApocalypseEngine/Window.h>
#include <ApocalypseEngine/StaticShader.h>
#include <ApocalypseEngine/Camera.h>
#include <ApocalypseEngine/GLTexture.h>
#include <ApocalypseEngine/Asset.h>
#include <ApocalypseEngine/InputManager.h>
#include <ApocalypseEngine/Timing.h>
#include <ApocalypseEngine/BaseLight.h>
#include <ApocalypseEngine/PhysicsCore.h>
#include <ApocalypseEngine/Rectangle.h>

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
	PhysicsCore _physics;

	BaseLight _light;
	BaseLight _sun;

	Player* _player = new Player(glm::vec3(0.0f, 0.0f, 0.0f), CollisionType::RECTANGLE);
	Actor* _monkey = new Actor(glm::vec3(2.0f, 4.0f, 0.0), CollisionType::RECTANGLE);
	Actor* _monkey2 = new Actor(glm::vec3(12.0f, 8.0f, 0.0), CollisionType::RECTANGLE, 0.0f, glm::vec3(0.0f,1.0f,0.0f), 3.0f);

	GLTexture _standard;
	GLTexture _standard1;

	std::vector<Vertex> _vertices;
	std::vector<Asset*> _assets;
	std::vector<BaseLight> _lights;
	std::vector<Actor*> _actors;

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
	void gameLoop();
	void cleanUp();

	const std::string VERSION = "v0.1.2";
};