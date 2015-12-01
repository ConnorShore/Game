#include "Box.h"


Box::Box()
{
}

Box::~Box()
{
}

void Box::init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimension, GLTexture texture, bool fixedRotation, const glm::vec4 & uvRect)
{
	_texture = texture;
	_dimension = dimension;
	_uvRect = uvRect;

	b2BodyDef bodyDef;

	/*if(dynamicBody) */bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = fixedRotation;
	_body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;

	/*if(dynamicBody)*/ fixtureDef.friction = 0.3f;
	//else fixtureDef.friction = 0.0f;

	_fixture = _body->CreateFixture(&fixtureDef);
}

void Box::render(SpriteBatch& spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = _body->GetPosition().x - _dimension.x / 2.0f;
	destRect.y = _body->GetPosition().y - _dimension.y / 2.0f;
	destRect.z = _dimension.x;
	destRect.w = _dimension.y;
	spriteBatch.addToBatch(destRect, _uvRect, 0.0f, _texture.id, Color(255, 255, 255, 255), _body->GetAngle());
}