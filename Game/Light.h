#pragma once

#include <glm/glm.hpp>

struct Light
{
	glm::vec3 _position;
	glm::vec3 _color;

	void init(glm::vec3& position, glm::vec3& color) {
		_position = position;
		_color = color;
	}

	glm::vec3 getPosition() const { return _position; }
	glm::vec3 getColor() const { return _color; }

	void setPosition(glm::vec3& newPos) { _position = newPos; }
	void setColor(glm::vec3& newCol) { _color = newCol; }
};

