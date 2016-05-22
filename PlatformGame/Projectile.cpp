#include "Projectile.h"

#include <ApocalypseEngine\ResourceManager.h>


Projectile::Projectile(b2World* world, const glm::vec2 & position, const glm::vec2 & direction, float speed, 
	const std::string & texturePath, float size /* 1.0f */, bool gravity /* false */) :
	position_(position), direction_(direction), speed_(speed), texture_(ResourceManager::getTexture(texturePath)), size_(size), gravity_(gravity)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.gravityScale = 0.0f;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.linearVelocity.Set(direction.x * speed, direction.y * speed);
	//bodyDef.bullet = true;
	body_ = world->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = size_ / 2.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.friction = 0.0f;
	fixtureDef.density = 0.0f;
	fixture_ = body_->CreateFixture(&fixtureDef);
}

Projectile::~Projectile()
{
}
