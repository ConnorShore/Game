#include "Bullet.h"

#include <ApocalypseEngine\ResourceManager.h>

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float speed, const std::string& texturePath)
	: _position(position), _direction(direction), _speed(speed), _size(10.0f), _texture(ResourceManager::getTexture(texturePath))
{
}

void Bullet::update()
{
	_position += _direction * _speed;
}

void Bullet::render(SpriteBatch& spriteBatch)
{
	glm::vec4 destRect(_position.x, _position.y, _size, _size);
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	spriteBatch.addToBatch(destRect, uvRect, 0, _texture.id, color);
}

Bullet::~Bullet()
{
}
