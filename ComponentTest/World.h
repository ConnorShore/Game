#pragma once

#include "Entity.h"
#include "EntityFactory.h"
#include "ComponentFactory.h"

class World
{
public:
	World();
	~World();

	void addSystem(ComponentFactory* system);

	void update();

private:
	EntityFactory* entityFactory;
	std::vector<ComponentFactory*> _systems;
};

