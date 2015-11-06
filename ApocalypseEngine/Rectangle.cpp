#include "Rectangle.h"



Rectangle::Rectangle(glm::vec3 position, glm::vec3 dimension) : _position(position), _dimension(dimension)
{
}

Rectangle::Rectangle()
{
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_dimension = glm::vec3(0.0f, 0.0f, 0.0f);
}

Rectangle::~Rectangle()
{
}