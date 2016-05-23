#pragma once

#include "Component.h"

#include <vector>

class Component;

enum SystemType {PHYSICS, RENDER, CONTROL};

class ComponentFactory
{
public:
	ComponentFactory(const SystemType sysType);
	~ComponentFactory();

	Component* createComponent(const std::string& name);
	//Component* addComponent(const std::string& name);
	Component* removeComponent(const std::string& name);
	
	virtual void update() = 0;	//update components

	SystemType getSystemType() const { return type; }

protected:
	SystemType type;
	std::vector<Component*> _components;
};

