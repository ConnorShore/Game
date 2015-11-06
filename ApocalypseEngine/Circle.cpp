#include "Circle.h"



Circle::Circle(glm::vec3 position, float radius) : _position(position), _radius(radius)
{
}

Circle::Circle()
{
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_radius = 1.0f;
}

Circle::~Circle()
{
}
