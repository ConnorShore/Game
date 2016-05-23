#include "Entity.h"

#include <iostream>
#include <fstream>


Entity::Entity(std::string id) : _id(id)
{
}

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::addComponent(Component* comp)
{
	_components.push_back(comp);
	comp->parent = this;
	//_componentFactory->createComponent(comp->name);
}

Component* Entity::removeComponent(const std::string& name)
{
	return nullptr;
}

void Entity::serialize(const std::string& fileName)
{
	std::ofstream file(fileName);
	if (file.is_open()) {
		file << _id << "\n";
		file.close();
	}
	else {
		std::cout << "Unable to open file: " << fileName << std::endl;
	}

	std::cout << "File creation successful!\n";
}

void Entity::deserialize(const std::string& fileName)
{
}
