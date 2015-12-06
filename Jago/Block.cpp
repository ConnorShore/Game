#include "Block.h"


Block::Block()
{
}

Block::~Block()
{
}

void Block::init(b2World * _world, const glm::vec2 & position, GLTexture texture, float depth, bool collidable)
{
	_texture = texture;
	_depth = depth;
	_collidable = collidable;

	_staticBox.init(_world, position, glm::vec2(_size), _texture, true, _collidable);
}

void Block::update()
{
	
}

void Block::render(SpriteBatch & spriteBatch)
{
	glm::vec4 destRect;
	glm::vec2 position(_staticBox.getPosition().x, _staticBox.getPosition().y);

	destRect.x = position.x - _size / 2.0f;
	destRect.y = position.y - _size / 2.0f;
	destRect.z = _size;
	destRect.w = _size;

	spriteBatch.addToBatch(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), _depth, _texture.id, Color(_brightness, _brightness, _brightness, 255));
}