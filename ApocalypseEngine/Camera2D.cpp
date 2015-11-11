#include "Camera2D.h"



Camera2D::Camera2D() :  _matrixUpdate(true), _scale(1.0), _screenWidth(1280), _screenHeight(720),
	_position(0.0f, 0.0f), _cameraMatrix(1.0f), _orthoMatrix(1.0f)
{
}

void Camera2D::init(int screenWidth, int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
}

void Camera2D::update()
{
	if (_matrixUpdate) {
		glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
		_cameraMatrix = glm::translate(_orthoMatrix, translate);
		glm::vec3 scale(_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

		_matrixUpdate = false;
	}
}

glm::vec2 Camera2D::convertToWorldCoords(glm::vec2 screenCoords)
{
	//Make 0 the center
	screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
	//Scale coords
	screenCoords /= _scale;
	//Translate with camera pos
	screenCoords += glm::vec2(_position.x, -_position.y);

	return screenCoords;
}

Camera2D::~Camera2D()
{
}
