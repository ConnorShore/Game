#pragma once

#include <glm/glm.hpp>

class BaseLight
{

public:
	BaseLight();
	~BaseLight();

	void init(glm::vec3& position, glm::vec3& color);
	void init(glm::vec3& position, glm::vec3& color, glm::vec3& attenuation);

	glm::vec3 getPosition() const { return _position; }
	glm::vec3 getColor() const { return _color; }
	glm::vec3 getAttenuation() const { return _attenuation; }

	void setPosition(glm::vec3& newPos) { _position = newPos; }
	void setColor(glm::vec3& newCol) { _color = newCol; }
	void setAttenuation(glm::vec3& newAtt) { _attenuation = newAtt; }

private:
	glm::vec3 _position;
	glm::vec3 _color;
	glm::vec3 _attenuation;
};