#pragma once

#include "Component.h"
#include "ComponentFactory.h"

#include <vector>

class Entity
{
public:
	Entity(std::string id);
	~Entity();

	void addComponent(Component* comp);
	Component* removeComponent(const std::string& name);

	//void sendMessage(Message* msg); <-- Implement

	std::string const getID() { return _id; }

	void serialize(FILE file);
	void deserialize(FILE file);

private:
	std::string _id;
	std::vector<Component*> _components;
};