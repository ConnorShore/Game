#pragma once

#include "Window.h"
#include "Loader.h"
#include "Camera.h"
#include "Vertex.h"
#include "GLTexture.h"
#include "Loader.h"
#include "Asset.h"
#include "InputManager.h"

#include <glm/glm.hpp>

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

	std::vector<Vertex> vertices;

	//std::vector<glm::vec3> vertices, normals;
	//std::vector<glm::vec2> uvs;
	Asset _player;

	GLuint _programID;
	int _screenWidth, _screenHeight;

	void initSystems();
	void initShaders();
	void input();
	void update();
	void render();
	void bindUniforms();
	void gameLoop();
	void cleanUp();
};
