#include "Light.h"


Light::Light()
{
}

void Light::init(glm::vec3& position, glm::vec3& color) {
	_position = position;
	_color = color;
}

Light::~Light()
{
}