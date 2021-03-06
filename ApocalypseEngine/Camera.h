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

	float getPitch() const { return _pitch; }
	float getYaw() const { return _yaw; }
	float getSensitivity() const { return _sensitivity; }
	float getCamSpeed() const { return _camSpeed; }
	float getFollowDist() const { return _followDist; }

	bool isMouseLook() const { return _mouseLook; }
	bool isFreeCam() const { return _freeCam; }

	//Setters
	void setPosition(glm::vec3& newPos) { _position = newPos; }
	void setMousePos(glm::ivec2& newPos) { _mousePos = newPos; }
	void setDirection(glm::vec3& newDir) { _direction = newDir; }
	void setRight(glm::vec3& newDir) { _right = newDir; }
	void setUp(glm::vec3& newDir) { _up = newDir; }
	void setVertAngle(float newAngle) { _pitch = newAngle; }
	void setHorzAngle(float newAngle) { _yaw = newAngle; }
	void setSensitivity(float newSpeed) { _sensitivity = newSpeed; }
	void setMouseLook(bool look) { _mouseLook = look; }
	void setFreeCam(bool free) { _freeCam = free; }
	void setFollowDist(float dist) { _followDist = dist; }

private:
	InputManager _inputManager;
	Window _window;

	glm::vec3 _modelPos;

	int _screenWidth, _screenHeight;
	bool _needsUpdate;
	bool _freeCam = false;
	float _yaw, _pitch, _sensitivity, _fov, _camSpeed;
	bool _mouseLook = true;

	const float MAX_ANGLE = 1.49f;

	float _followDist = 20.0f;

	glm::ivec2 _mousePos;
	glm::vec3 _position, _direction, _right, _up;
	glm::mat4 _viewMatrix;

	void look();
	void mouseLook();
};
