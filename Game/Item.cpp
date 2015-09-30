#include "Item.h"



Item::Item(const std::string& name, glm::vec3& position, float rotation /*0.0f*/, glm::vec3& rotationAxis /*glm::vec3(0.0f,1.0f,0.0f)*/, float scale /*1.0f*/)
	: Asset(position, rotation, rotationAxis, scale), _name(name)
{
}

Item::Item(const std::string & name, glm::vec3& position, bool holdable) : Asset(position), _name(name), _holdable(holdable)
{
}

Item::~Item()
{
}