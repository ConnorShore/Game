#pragma once

#include <glm/glm.hpp>

class Light
{

public:
	Light();
	~Light();

	void init(glm::vec3& position, glm::vec3& color);

	glm::vec3 getPosition() const { return _position; }
	glm::vec3 getColor() const { return _color; }

	void setPosition(glm::vec3& newPos) { _position = newPos; }
	void setColor(glm::vec3& newCol) { _color = newCol; }

private:
	glm::vec3 _position;
	glm::vec3 _color;
};