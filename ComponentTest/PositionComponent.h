#pragma once

#include "Component.h"

class PositionComponent : public Component
{
public:
	PositionComponent();
	~PositionComponent();

	virtual void update();
	virtual void serialize(const std::string& fileName);
	virtual void deserialize(const std::string& fileName);

private:
	float _x, _y;
};

