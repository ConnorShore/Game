#include "Torch.h"

#include <ApocalypseEngine\ResourceManager.h>

Torch::Torch()
{
}

Torch::~Torch()
{
}

void Torch::init(const glm::vec2& position, float size, Color color)
{
	_position = position;
	_dimension = glm::vec2(0.25f, 0.65f);

	_light.color = color;
	_light.size = size;

	_light.position = glm::vec2(_position.x, _position.y + _dimension.y);

	_texture = ResourceManager::getTexture("Textures/torch.png");
}

void Torch::update()
{
	static float initSize = _light.size;
	static GLubyte initPow = _light.color.a;

	_light.size = initSize + (glm::cos(_count) / 2.5f);
	_count += 0.05f;
}

void Torch::render(SpriteBatch& spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = _position.x - _dimension.x / 2.0f;
	destRect.y = _position.y;
	destRect.z = _dimension.x;
	destRect.w = _dimension.y;

	spriteBatch.addToBatch(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 1.0f, _texture.id, Color(255, 255, 255, 255));
}
