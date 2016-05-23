#include "ComponentFactory.h"

#include <iostream>
#include <fstream>


ComponentFactory::ComponentFactory(const SystemType sysType) : type(sysType)
{
}

ComponentFactory::~ComponentFactory()
{
}

Component* ComponentFactory::createComponent(const std::string& name)
{
	//Append component and data to file (Entity parent file)
	return nullptr;
}

//Component* ComponentFactory::addComponent(const std::string& name)
//{
//	if (name == "Position") {
//		//return new PositionComponent();
//	}
//	else if (name == "Velocity") {
//		//return new VelocityComponent();
//	}
//	else if (name == "Sprite") {
//		//return new SpriteComponent();
//	}
//	else {
//		std::cout << "Component does not exist" << std::endl;
//	}
//
//	return nullptr;
//}

Component* ComponentFactory::removeComponent(const std::string& name)
{
	return nullptr;
}
