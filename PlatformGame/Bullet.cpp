#include "Bullet.h"

#include <ApocalypseEngine\ResourceManager.h>

Bullet::Bullet(b2World * world, const glm::vec2 & position, const glm::vec2 & direction, float speed, const std::string& texPath, float size /* 1.0f */, float spread /* 0.0f */) :
	Projectile(world, position, direction, speed, texPath, size), _spread(spread)
{
}

Bullet::Bullet(b2World* world, const glm::vec2 & position, const glm::vec2 & direction, float speed, float size, float spread /* 0.0f */) :
	Projectile(world, position, direction, speed, "Textures/Bullet.png", size)
{
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	body_->ApplyLinearImpulse(b2Vec2(direction_.x * speed_, direction_.y * speed_), b2Vec2(position_.x, position_.y));
}

void Bullet::render(SpriteBatch& spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = body_->GetPosition().x - size_ / 2.0f;
	destRect.y = body_->GetPosition().y - size_ / 2.0f;
	destRect.z = destRect.w = size_;
	spriteBatch.addToBatch(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 0.0f, texture_.id, Color(255, 255, 255, 255), body_->GetAngle());
}
