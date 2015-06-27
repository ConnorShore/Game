#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(glm::vec3 position) : _position(position), _scale(1.0f), 
	_cameraMatrix(1.0f), _needsUpdate(true)
{
}

Camera::Camera() : _position(glm::vec3(0.0f,0.0f,0.0f)), _scale(1.0f), 
	_cameraMatrix(1.0f), _needsUpdate(true)
{
}

void Camera::init(int screenWidth, int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
}

glm::mat4 Camera::getMatrix()
{
	glm::vec3 translate = glm::vec3(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, _position.z);
	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), translate);

	glm::vec3 scale = glm::vec3(_scale, _scale, _scale);
	modelMatrix = modelMatrix * glm::scale(glm::mat4(1.0f), scale);

	glm::mat4 viewMatrix = glm::lookAt(_position, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projMatrix = glm::perspective(70.0f, (float)_screenWidth / (float) _screenHeight, 0.1f, 100.0f);

	_cameraMatrix = projMatrix * modelMatrix * viewMatrix;

	return _cameraMatrix;
}

void Camera::update()
{
	if (_needsUpdate) {


		_needsUpdate = false;
	}
}

Camera::~Camera()
{
}
