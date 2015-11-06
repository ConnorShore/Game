#pragma once

#include <glm\glm.hpp>

class Circle
{
public:
	Circle(glm::vec3 position, float radius);
	Circle();
	~Circle();

	glm::vec3 getPosition() const { return _position; }
	float getRadius() const { return _radius; }

	void setPosition(glm::vec3& newPos) { _position = newPos; }
	void setRadius(float newRad) { _radius = newRad; }

private:
	glm::vec3 _position;
	float _radius;
};

