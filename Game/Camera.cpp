#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <SDL/SDL.h>

Camera::Camera() : _needsUpdate(true), _horizontalAngle(3.1415f), _verticalAngle(0.0f)
{
}

void Camera::init(glm::vec3 position, int screenWidth, int screenHeight, float fieldOfView, float cameraSpeed)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);

	_position = position;
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
}

void Camera::look()
{
	_direction = glm::vec3(
		cos(_verticalAngle) * sin(_horizontalAngle),
		sin(_verticalAngle),
		cos(_verticalAngle) * cos(_horizontalAngle));

	_right = glm::vec3(
		sin(_horizontalAngle - 3.14f / 2.0f),
		0,
		cos(_horizontalAngle - 3.14f / 2.0f));

	_up = glm::cross(_right, _direction);
}

glm::mat4 Camera::getMatrix()
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
	glm::mat4 view = glm::lookAt(_position, _position+_direction, _up);
	glm::mat4 projection = glm::perspective(70.0f, 1.0f*_screenWidth / _screenHeight, 0.1f, 100.0f);

	_cameraMatrix = projection * view * model;

	return _cameraMatrix;
}

void Camera::update()
{
	look();
	getMatrix();
}

Camera::~Camera()
{
}
