#pragma once

#include "Component.h"

#include <map>

enum SystemType {PHYSICS, RENDER, CONTROL};

class ComponentSystem
{
public:
	ComponentSystem(const SystemType sysType);
	~ComponentSystem();

	Component* addComponent(const std::string& name);
	Component* removeComponent(ComponentType comp);
	
	virtual void update() = 0;	//update components

	SystemType getSystemType() const { return type; }

protected:
	SystemType type;
	std::map<std::string, Component*> _components;
};

