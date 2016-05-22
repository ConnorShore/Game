#include "Tile.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}


void Tile::init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimension, GLTexture texture, glm::vec4 uvRect)
{
	_dimension = dimension;
	_texture = texture;
	_uvRect = uvRect;

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	_body = world->CreateBody(&bodyDef);	//< Create the body

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	_fixture = _body->CreateFixture(&fixtureDef);
}

void Tile::init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimension)
{
	_dimension = dimension;

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	_body = world->CreateBody(&bodyDef);	//< Create the body

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	_fixture = _body->CreateFixture(&fixtureDef);
}

void Tile::render(SpriteBatch& spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = _body->GetPosition().x - _dimension.x / 2.0f;
	destRect.y = _body->GetPosition().y - _dimension.y / 2.0f;
	destRect.z = _dimension.x;
	destRect.w = _dimension.y;

	spriteBatch.addToBatch(destRect, _uvRect, 0.0f, _texture.id, Color(255, 255, 255, 255), _body->GetAngle());
}