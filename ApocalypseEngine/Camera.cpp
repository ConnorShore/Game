#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <SDL/SDL.h>

Camera::Camera() : _needsUpdate(true), _yaw(3.1415f), _pitch(0.0f)
{
}

void Camera::init(glm::vec3 position, int screenWidth, int screenHeight, float fieldOfView, float cameraSpeed, float sensitivity)
{
	SDL_ShowCursor(0);

	_position = position;
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_fov = fieldOfView;
	_camSpeed = cameraSpeed;
	_sensitivity = sensitivity;
}

void Camera::look()
{
	_direction = glm::vec3(
		cos(_pitch) * sin(_yaw),
		sin(_pitch),
		cos(_pitch) * cos(_yaw));

	_right = glm::vec3(
		sin(_yaw - 3.14f / 2.0f),
		0,
		cos(_yaw - 3.14f / 2.0f));

	_up = glm::cross(_right, _direction);
}

void Camera::mouseLook()
{
	static int _midWidth = _screenWidth / 2;
	static int _midHeight = _screenHeight / 2;

	_mousePos.x = _midWidth;
	_mousePos.y = _midHeight;

	SDL_GetMouseState(&_mousePos.x, &_mousePos.y);
	SDL_WarpMouseInWindow(_window.getSDLWindow(), _midWidth, _midHeight);

	_yaw += _sensitivity * float(_midWidth - _mousePos.x);
	_pitch += _sensitivity * float(_midHeight - _mousePos.y);

	if (_pitch >= MAX_ANGLE)
		_pitch = MAX_ANGLE;

	if (_pitch <= -MAX_ANGLE)
		_pitch = -MAX_ANGLE;
}

glm::mat4 Camera::createViewMatrix()
{

	glm::mat4 view = glm::lookAt(_position, _position + _direction, _up);
	_viewMatrix = view;
	return _viewMatrix;
}

glm::mat4 Camera::createProjectionMatrix()
{
	glm::mat4 projection = glm::perspective(_fov, 1.0f * _screenWidth / _screenHeight, 0.1f, 100.0f);
	return projection;
}

void Camera::update()
{
	look();
	if (_mouseLook)
		mouseLook();
}

Camera::~Camera()
{
}