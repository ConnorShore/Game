#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : _needsUpdate(true)
{
}

void Camera::init(glm::vec3 position, int screenWidth, int screenHeight, float fieldOfView, float cameraSpeed)
{
	_position = position;
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
}

glm::mat4 Camera::getMatrix()
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
	glm::mat4 view = glm::lookAt(_position, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 projection = glm::perspective(70.0f, 1.0f*_screenWidth / _screenHeight, 0.1f, 100.0f);

	_cameraMatrix = projection * view * model;

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
