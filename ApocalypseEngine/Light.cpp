#include "Light.h"


Light::Light()
{
}

void Light::init(glm::vec3& position, glm::vec3& color) {
	_position = position;
	_color = color;
}

void Light::init(glm::vec3 & position, glm::vec3 & color, glm::vec3 & attenuation)
{
	_position = position;
	_color = color;
	_attenuation = attenuation;
}

Light::~Light()
{
}