#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(glm::vec3 position);
	Camera();
	~Camera();

	void init(int screenWidth, int screenHeight);
	void update();
	glm::mat4 getMatrix();

	void setPosition(glm::vec3 newPos) { _position = newPos; _needsUpdate = true; }
	void setScale(float scale) { _scale = scale; _needsUpdate = true; }

	glm::vec3 getPosition() { return _position; }
	float getScale() { return _scale; }
	glm::mat4 getCameraMatrix() { return _cameraMatrix; }

private:
	int _screenWidth, _screenHeight;
	float _scale;
	bool _needsUpdate;

	glm::vec3 _position;
	glm::mat4 _cameraMatrix, _viewMatrix;
};

