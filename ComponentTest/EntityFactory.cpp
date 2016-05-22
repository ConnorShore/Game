#include "EntityFactory.h"

#include <stdio.h>

EntityFactory::EntityFactory()
{
}

Entity* EntityFactory::createEntity(const std::string& name)
{
	Entity* entity = new Entity(name);	//Move to writing this to file (serialization)
	
	addEntity(entity);
	return entity;
}

void EntityFactory::addEntity(Entity* entity)
{
	_entities.push_back(entity);
}

Entity* EntityFactory::removeEntity(const std::string& id)
{
	int size = _entities.size();
	Entity* temp = nullptr;
	for (int i = 0; i < size; i++) {
		if (id == _entities[i]->getID()) {
			temp = _entities[i];
			_entities.erase(_entities.begin() + i);
			return;
		}
	}

	return temp;
}

Entity * EntityFactory::getEntity(const std::string & id)
{
	int size = _entities.size();
	for (int i = 0; i < size; i++) {
		if (id == _entities[i]->getID()) return _entities[i];
	}

	return nullptr;
}

EntityFactory::~EntityFactory()
{
}
