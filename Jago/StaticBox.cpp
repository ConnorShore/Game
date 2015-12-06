#include "StaticBox.h"



StaticBox::StaticBox()
{
}


StaticBox::~StaticBox()
{
}

void StaticBox::init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimension, GLTexture texture, bool lightAffected /*true*/, bool collidable /* false */)
{
	_position = position;
	_dimension = dimension;
	_texture = texture;
	_lightAffected = lightAffected;
	_collidable = collidable;

	if (lightAffected) _brightness = 75;
	else _brightness = 255;

	if (_collidable) {
		//Make the ground
		b2BodyDef bodyDef;
		bodyDef.position.Set(position.x, position.y);
		_body = world->CreateBody(&bodyDef);

		//Make ground fixture (hit box);
		b2PolygonShape box;
		box.SetAsBox(dimension.x, dimension.y);
		_body->CreateFixture(&box, 0.0f);	//< Density is 0 because it is static
	}
}

void StaticBox::init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimension)
{
	_position = position;
	_dimension = dimension;
	_lightAffected = false;

	//Make the ground
	b2BodyDef bodyDef;
	bodyDef.position.Set(position.x, position.y);
	_body = world->CreateBody(&bodyDef);

	//Make ground fixture (hit box);
	b2PolygonShape box;
	box.SetAsBox(dimension.x, dimension.y);
	_body->CreateFixture(&box, 0.0f);	//< Density is 0 because it is static
}

void StaticBox::update()
{

}

void StaticBox::render(SpriteBatch & spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = _position.x - _dimension.x;
	destRect.y = _position.y - _dimension.y;
	destRect.z = _dimension.x * 2.0f;
	destRect.w = _dimension.y * 2.0f;
	spriteBatch.addToBatch(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 2.0f, _texture.id, Color(_brightness, _brightness, _brightness, 255));
}
