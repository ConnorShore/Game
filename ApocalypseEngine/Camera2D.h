#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera2D
{
public:
	Camera2D();
	~Camera2D();

	void init(int screenWidth, int screenHeight);
	void update();

	glm::vec2 convertToWorldCoords(glm::vec2 screenCoords);

	float getScale() const { return _scale; }
	glm::vec2 getPosition() const { return _position; }
	glm::mat4 getCameraMatrix() const { return _cameraMatrix; }

	void setScale(float newSize) { _scale = newSize; _matrixUpdate = true; }
	void setPosition(glm::vec2& newPos) { _position = newPos; _matrixUpdate = true; }

private:
	bool _matrixUpdate;
	int _screenWidth, _screenHeight;
	float _scale;

	glm::vec2 _position;
	glm::mat4 _cameraMatrix, _orthoMatrix;
};