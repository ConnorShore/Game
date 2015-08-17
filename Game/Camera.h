#pragma once

#include "InputManager.h"
#include "Window.h"

#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void init(glm::vec3 position, int screenWidth, int screenHeight, float fieldOfView, float cameraSpeed, float sensitivity);
	void update();

	glm::mat4 createViewMatrix();
	glm::mat4 createProjectionMatrix();

	//Getters
	glm::ivec2 getMousePos() const { return _mousePos; }
	glm::vec3 getPosition() const { return _position; }
	glm::vec3 getDirection() const { return _direction; }
	glm::vec3 getRight() const { return _right; }
	glm::vec3 getUp() const { return _up; }
	glm::mat4 getViewMatrix() const { return _viewMatrix; }

	float getVertAngle() const { return _verticalAngle; }
	float getHorzAngle() const { return _horizontalAngle; }
	float getSensitivity() const { return _sensitivity; }
	float getCamSpeed() const { return _camSpeed; }

	bool isMouseLook() const { return _mouseLook; }

	//Setters
	void setPosition(glm::vec3& newPos) { _position = newPos; }
	void setMousePos(glm::ivec2& newPos) { _mousePos = newPos; }
	void setDirection(glm::vec3& newDir) { _direction = newDir; }
	void setRight(glm::vec3& newDir) { _right = newDir; }
	void setUp(glm::vec3& newDir) { _up = newDir; }
	void setVertAngle(float newAngle) { _verticalAngle = newAngle; }
	void setHorzAngle(float newAngle) { _horizontalAngle = newAngle; }
	void setSensitivity(float newSpeed) { _sensitivity = newSpeed; }
	void setMouseLook(bool look) { _mouseLook = look; }

private:
	InputManager _inputManager;
	Window _window;

	glm::vec3 _modelPos;

	int _screenWidth, _screenHeight;
	bool _needsUpdate;
	float _horizontalAngle, _verticalAngle, _sensitivity, _fov, _camSpeed;
	bool _mouseLook = true;

	const float MAX_ANGLE = 1.49f;

	glm::ivec2 _mousePos;
	glm::vec3 _position, _direction, _right, _up;
	glm::mat4 _viewMatrix;

	void look();
	void mouseLook();
};
