#include "ComponentSystem.h"

#include <iostream>


ComponentSystem::ComponentSystem(const SystemType sysType) : type(sysType)
{
}

ComponentSystem::~ComponentSystem()
{
}

Component* ComponentSystem::addComponent(const std::string& name)
{
	if (name == "Position") {
		//return new PositionComponent();
	}
	else if (name == "Velocity") {
		//return new VelocityComponent();
	}
	else if (name == "Sprite") {
		//return new SpriteComponent();
	}
	else {
		std::cout << "Component does not exist" << std::endl;
	}
}

Component* ComponentSystem::removeComponent(ComponentType comp)
{
	return nullptr;
}
