#include "Player.h"

#include <ApocalypseEngine\ResourceManager.h>
#include <SDL/SDL_keyboard.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimension)
{
	GLTexture texture = ResourceManager::getTexture("Textures/Player/idle_right.png");
	_collisionBox.init(world, position, dimension, texture, true /*fixedRotation*/);
}

void Player::update(InputManager inputManager)
{
	b2Body* body = _collisionBox.getBody();

	//Movement
	if (inputManager.isKeyDown(SDLK_a)) {
		body->ApplyForceToCenter(b2Vec2(-100.0f, 0.0f));
	}
	else if (inputManager.isKeyDown(SDLK_d)) {
		body->ApplyForceToCenter(b2Vec2(100.0f, 0.0f));
	}
	else {
		//Apply damping
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x * 0.95f, body->GetLinearVelocity().y));
	}

	//Cap the movement speed
	const float MAX_SPEED = 6.25f;
	if (body->GetLinearVelocity().x < -MAX_SPEED) {
		body->SetLinearVelocity(b2Vec2(-MAX_SPEED, body->GetLinearVelocity().y));
	}
	else if (body->GetLinearVelocity().x > MAX_SPEED) {
		body->SetLinearVelocity(b2Vec2(MAX_SPEED, body->GetLinearVelocity().y));
	}

	//Loop through all contact points
	for (b2ContactEdge* ce = body->GetContactList(); ce != nullptr; ce = ce->next) {
		b2Contact* c = ce->contact;
		if (c->IsTouching()) {
			b2WorldManifold manifold;
			c->GetWorldManifold(&manifold);

			//Check if points are below
			bool canJump = false;
			for (int i = 0; i < b2_maxManifoldPoints; i++) {
				if (manifold.points[i].y < body->GetPosition().y - _collisionBox.getDimension().y / 2.0f + 0.01f) {
					canJump = true;
					break;
				}
			}

			//Can jump
			const float MAX_JUMP_SPEED = 8.25f;
			if (canJump && body->GetLinearVelocity().y < MAX_JUMP_SPEED) {
				if (inputManager.isKeyDown(SDLK_w)) {
					body->ApplyLinearImpulse(b2Vec2(0.0f, 15.0f), b2Vec2(0.0f, 0.0f));
					break;
				}
			}
		}
	}
}

void Player::render(SpriteBatch& spriteBatch)
{
	_collisionBox.render(spriteBatch);
}
