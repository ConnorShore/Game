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
	comp->parent = this;
	_components.push_back(comp);

	switch(comp->type) {
		case CMP_VELOCITY:
			//_world->getPhysicsSystem()->addComponent(comp)
			break;
		case CMP_POSITION:
			//_world->getPhysicsSystem()->addComponent(comp)
			break;
		case CMP_DRAW:
			//_world->getRenderSystem()->addComponent(comp)
			break;
		case CMP_INPUT:
			//_world->getControlSystem()->addComponent(comp)
			break;
		default:
			std::cout << "Error: Component doesn't have a type" << std::endl;
			exit(-1);
			break;
	}
}

Component* Entity::removeComponent(ComponentType comp)
{
	Component* element;
	int size = _components.size();
	for (int i = 0; i < size; i++) {
		if (_components[i]->type == comp) {
			element = _components[i];
			_components.erase(_components.begin() + i);
			break;
		}
	}
	return element;
}
