#pragma once

#include <glm\glm.hpp>

class Rectangle
{
public:
	Rectangle(glm::vec3 position, glm::vec3 dimension);
	Rectangle(glm::vec2 position, glm::vec2 dimension);
	Rectangle();
	~Rectangle();

	glm::vec3 getPosition() const { return _position; }
	glm::vec3 getDimension() const { return _dimension; }
	glm::vec2 getPosition2D() const { return _position2D; }
	glm::vec2 getDimension2D() const { return _dimension2D; }

	void setPositionCentered(glm::vec3& newPos) { _position = newPos; }
	void setPosition(glm::vec3& newPos) { _position = glm::vec3(newPos.x - _dimension.x / 2.0f, newPos.y - _dimension.y / 2.0f, newPos.z); }
	void setDimension(glm::vec3& newDim) { _dimension = newDim; }

	void setPosition2DCentered(glm::vec2& newPos) { _position2D = newPos; }
	void setPosition2D(glm::vec2& newPos) { _position2D = glm::vec2(newPos.x - _dimension2D.x / 2.0f, newPos.y - _dimension2D.y / 2.0f); }
	void setDimension2D(glm::vec2& newDim) { _dimension2D = newDim; }

private:
	glm::vec3 _position, _dimension;
	glm::vec2 _position2D, _dimension2D;
	float _rotation;
};

