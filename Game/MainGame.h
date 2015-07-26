#pragma once

#include "Window.h"
#include "Loader.h"
#include "Camera.h"
#include "Vertex.h"
#include "GLTexture.h"
#include "Loader.h"
#include "Asset.h"
#include "InputManager.h"
#include "Timing.h"
#include "Player.h"	

#include <glm/glm.hpp>
#include <list>

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
	GLuint _vaoID, _vertexBuffer, _normalBuffer, _uvBuffer, _iboID;
	Camera _camera;
	InputManager _inputManager;
	Timing _timer;
	Player _player;
	Asset _test;

	std::vector<Vertex> _vertices;
	std::vector<Asset> _assets;

	GLuint _staticProgram;

	int _screenWidth, _screenHeight;

	float _playerSpeed = 0.25f;

	void initSystems();
	void initShaders();
	void input();
	void update();
	void render();
	void bindUniforms();
	void gameLoop();
	void cleanUp();
};
