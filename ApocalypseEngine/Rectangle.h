#pragma once

#include <glm\glm.hpp>

class Rectangle
{
public:
	Rectangle(glm::vec3 position, glm::vec3 dimension);
	Rectangle();
	~Rectangle();

	glm::vec3 getPosition() const { return _position; }
	glm::vec3 getDimension() const { return _dimension; }

	void setPositionCentered(glm::vec3& newPos) { _position = newPos; }
	void setPosition(glm::vec3& newPos) { _position = glm::vec3(newPos.x - _dimension.x / 2.0f, newPos.y - _dimension.y / 2.0f, newPos.z); }
	void setDimension(glm::vec3& newDim) { _dimension = newDim; }

private:
	glm::vec3 _position, _dimension;
	float _rotation;
};

