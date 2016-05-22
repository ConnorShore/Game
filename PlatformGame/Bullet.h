#pragma once

#include "Projectile.h"


class Bullet : public Projectile
{
public:
	Bullet(b2World* world, const glm::vec2& position, const glm::vec2& direction, float speed,
		const std::string& texPath, float size = 1.0f, float spread = 0.0f);
	Bullet(b2World* world, const glm::vec2& position, const glm::vec2& direction, float speed, float size = 1.0f, float spread = 0.0f);
	~Bullet();

	void update();
	void render(SpriteBatch& spriteBatch);

	inline float getSpread() { return _spread; }

private:
	float _spread;
};

