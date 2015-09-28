#include "BaseLight.h"


BaseLight::BaseLight()
{
}

void BaseLight::init(glm::vec3& position, glm::vec3& color) {
	_position = position;
	_color = color;
}

void BaseLight::init(glm::vec3 & position, glm::vec3 & color, glm::vec3 & attenuation)
{
	_position = position;
	_color = color;
	_attenuation = attenuation;
}

BaseLight::~BaseLight()
{
}