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
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = fixedRotation;
	_body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	_fixture = _body->CreateFixture(&fixtureDef);
}

void Box::init(b2World* world, const glm::vec2& position, const glm::vec2& dimension, bool fixedRotation /*true*/)
{
	_dimension = dimension;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = fixedRotation;
	_body = world->CreateBody(&bodyDef);	//< Create the body

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	_fixture = _body->CreateFixture(&fixtureDef);
}

void Box::update(std::vector<Light*> lights)
{
	for (Light* light : lights) {
		if (glm::abs(getPosition().x - light->getPosition().x) < (light->getLight().size / 2.0f)/* && glm::abs(getPosition().y - torch.getPosition().y) < torch.getLight().size / 2.0f*/) {
			_brightness = 255;
		}
		else if (glm::abs(getPosition().x - light->getPosition().x) > (light->getLight().size * 1.5f)/* && glm::abs(getPosition().y - torch.getPosition().y) > torch.getLight().size * 2.0f*/) {
			_brightness = 75;
		}
		else {
			float brightDist = 180 / (light->getLight().size / 2.0f - light->getLight().size * 1.5f);
			_brightness = (75 + (glm::abs(getPosition().x - light->getPosition().x) * brightDist));

			if (_brightness < 75) _brightness = 75;
			if (_brightness > 255) _brightness = 255;

			printf("%i\t%f\n", _brightness, brightDist);
		}
	}
}

void Box::render(SpriteBatch& spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = _body->GetPosition().x - _dimension.x / 2.0f;
	destRect.y = _body->GetPosition().y - _dimension.y / 2.0f;
	destRect.z = _dimension.x;
	destRect.w = _dimension.y;

	spriteBatch.addToBatch(destRect, _uvRect, 2.0f, _texture.id, Color(255, 255, 255, _brightness), _body->GetAngle());
}