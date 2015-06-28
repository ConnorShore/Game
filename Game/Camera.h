#pragma once

#include "InputManager.h"

#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void init(glm::vec3 position, int screenWidth, int screenHeight, float fieldOfView, float cameraSpeed);
	void move();
	void update();
	glm::mat4 getMatrix();

	void setPosition(glm::vec3 newPos) { _position = newPos; _needsUpdate = true; }

	glm::vec3 getPosition() { return _position; }
	glm::mat4 getCameraMatrix() { return _cameraMatrix; }

private:
	InputManager _inputManager;

	int _screenWidth, _screenHeight;
	bool _needsUpdate;

	glm::vec3 _position;
	glm::mat4 _cameraMatrix;
};

