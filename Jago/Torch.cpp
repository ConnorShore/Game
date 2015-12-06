#include "Torch.h"

#include <ApocalypseEngine\ResourceManager.h>

Torch::Torch()
{
}


Torch::~Torch()
{
}

void Torch::init(const glm::vec2 & position)
{
	_position = position;
	_texture = ResourceManager::getTexture("Textures/torch.png");
	_dimension = glm::vec2(0.25f, 0.75f);
	_flicker = true;

	initObj(_position, _dimension, 50.0f, Color(255, 255, 255, 85), _texture, _flicker);
}
