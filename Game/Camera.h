#pragma once

#include "InputManager.h"
#include "Asset.h"

#include <glm/glm.hpp>
#include "Window.h"

class Camera
{
public:
	Camera();
	~Camera();

	void init(glm::vec3 position, int screenWidth, int screenHeight, float fieldOfView, float cameraSpeed);
	void update();
	glm::mat4 getMatrix();

	//Getters
	glm::vec2 getMousePos() const { return _mousePos; }
	glm::vec3 getPosition() const { return _position; }
	glm::vec3 getDirection() const  { return _direction; }
	glm::vec3 getRight() const  { return _right; }
	glm::vec3 getUp() const  { return _up; }
	glm::mat4 getCameraMatrix() const  { return _cameraMatrix; }

	float getVertAngle() const { return _verticalAngle; }
	float getHorzAngle() const { return _horizontalAngle; }
	float getSensitivity() const { return _sensitivity; }
	float getCamSpeed() const { return _camSpeed; }

	//Setters
	void setPosition(glm::vec3& newPos) { _position = newPos; }
	void setMousePos(glm::vec2& newPos) { _mousePos = newPos; }
	void setDirection(glm::vec3& newDir) { _direction = newDir; }
	void setRight(glm::vec3& newDir) { _right = newDir; }
	void setUp(glm::vec3& newDir) { _up = newDir; }
	void setVertAngle(float newAngle) { _verticalAngle = newAngle; }
	void setHorzAngle(float newAngle) { _horizontalAngle = newAngle; }
	void setSensitivity(float newSpeed) { _sensitivity = newSpeed; }

private:
	InputManager _inputManager;
	Window _window;
	
	glm::vec3 _modelPos;

	std::vector<Asset> _assets;

	int _screenWidth, _screenHeight;
	bool _needsUpdate;
	float _horizontalAngle, _verticalAngle, _fov = 60.0f, _camSpeed = 3.0f, _sensitivity = 0.005f;
	
	glm::vec2 _mousePos;
	glm::vec3 _position, _direction, _right, _up;
	glm::mat4 _cameraMatrix;

	void look();
	void move();
};

