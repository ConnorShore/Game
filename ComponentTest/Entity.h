#pragma once

#include "Component.h"
#include "World.h"

#include <vector>

class Entity
{
public:
	Entity(std::string id);
	~Entity();

	void addComponent(Component* comp);
	Component* removeComponent(ComponentType comp);

	//void sendMessage(Message* msg); <-- Implement

	std::string const getID() { return _id; }

private:
	std::string _id;
	std::vector<Component*> _components;
};