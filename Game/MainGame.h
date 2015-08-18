#pragma once

#include "Window.h"
#include "StaticShader.h"
#include "Camera.h"
#include "GLTexture.h"
#include "Asset.h"
#include "InputManager.h"
#include "Timing.h"
#include "Light.h"

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
	Asset* _test = new Asset(glm::vec3(2.0f, 0.0f, -4.0f));
	GLTexture _standard;

	std::vector<Vertex> _vertices;
	std::vector<Asset*> _assets;

	GLuint _vaoID;

	glm::mat4 _projectionMatrix;

	int _screenWidth, _screenHeight;
	int showCursor = 0;

	float _playerSpeed = 0.25f;

	void initSystems();
	void initShaders();
	void initLights();
	void input();
	void update();
	void render();
	void bindUniforms();
	void gameLoop();
	void cleanUp();
};