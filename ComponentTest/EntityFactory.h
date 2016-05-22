#pragma once

#include "Entity.h"

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

	Entity* createEntity(const std::string& name);
	void addEntity(Entity* entity);
	Entity* removeEntity(const std::string& id);

	Entity* getEntity(const std::string& id);

	std::vector<Entity*> getEntities() const { return _entities; }

private:
	std::vector<Entity*> _entities;
};