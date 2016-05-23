#pragma once

#include "Component.h"
#include "ComponentFactory.h"

#include <vector>

class Component;

class Entity
{
public:
	Entity(std::string id);
	Entity();
	~Entity();

	void addComponent(Component* comp);
	Component* removeComponent(const std::string& name);

	//void sendMessage(Message* msg); <-- Implement

	std::string const getID() { return _id; }

	void serialize(const std::string& fileName);
	void deserialize(const std::string& fileNamee);

private:
	ComponentFactory* _componentFactory;
	std::string _id;
	std::vector<Component*> _components;
};