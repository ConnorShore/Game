#include "Entity.h"

#include <iostream>


Entity::Entity(std::string id) : _id(id)
{
}

Entity::~Entity()
{
}

void Entity::addComponent(Component* comp)
{
	_components.push_back(comp);
	comp->parent = this;
}

Component* Entity::removeComponent(const std::string& name)
{
	return nullptr;
}
