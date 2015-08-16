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
#include "StaticShader.h"
#include "ShaderProgram.h"

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
	StaticShader _staticShader;
	GameState _currentState;
	GLuint _vaoID, _vertexBuffer, _normalBuffer, _uvBuffer, _iboID;
	Camera _camera;
	InputManager _inputManager;
	Timing _timer;
	Asset* _test = new Asset(glm::vec3(2.0f, 0.0f, -4.0f));

	std::vector<Vertex> _vertices;
	//std::vector<ShaderProgram> _programs;
	std::vector<Asset*> _assets;


	int _screenWidth, _screenHeight;
	int showCursor = 0;

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
