#pragma once

#include "Light.h"

class Torch : public Light
{
public:
	Torch();
	~Torch();

	void init(const glm::vec2& position);

private:

};

