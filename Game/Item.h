#pragma once

#include "Asset.h"

#include <string>

class Item : public Asset
{
public:
	Item(const std::string& name, glm::vec3& position, float rotation = 0.0f, glm::vec3& rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f), float scale = 1.0f);
	Item(const std::string& name, glm::vec3& position, bool holdable);
	~Item();

	std::string getName() const { return _name; }
	bool isHoldable() const { return _holdable; }

private:
	std::string _name;
	bool _holdable;
};

