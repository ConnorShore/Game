#include "Player.h"

#include <SDL/SDL_keyboard.h>
#include <iostream>

#include <ApocalypseEngine\ResourceManager.h>
#include <ApocalypseEngine\GLTexture.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(b2World* world, const glm::vec2& position, const glm::vec2& dimension, const glm::vec2& drawDim)
{
	_dimension = dimension;
	_drawDim = drawDim;

	GLTexture texture = ResourceManager::getTexture("Textures/Player/ss_player.png");

	_collisionBox.init(world, position, dimension, true /*fixedRotation*/);
	_texture.init(texture, glm::ivec2(10, 10));
}

void Player::update(InputManager inputManager)
{
	b2Body* body = _collisionBox.getBody();

	//Movement
	if (inputManager.isKeyDown(SDLK_a)) {
		body->ApplyForceToCenter(b2Vec2(-100.0f, 0.0f));
		_direction = -1;
	}
	else if (inputManager.isKeyDown(SDLK_d)) {
		body->ApplyForceToCenter(b2Vec2(100.0f, 0.0f));
		_direction = 1;
	}
	else {
		//Apply damping
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x * 0.95f, body->GetLinearVelocity().y));
	}

	//Check for punching
	if (inputManager.isKeyPressed(SDLK_SPACE)) {
		_attacking = true;
	}

	//Cap the movement speed
	const float MAX_SPEED = 6.25f;
	_onGround = false;
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
			if (canJump) {
				_onGround = true;
				if (inputManager.isKeyPressed(SDLK_w)) {
					body->ApplyLinearImpulse(b2Vec2(0.0f, 20.0f), b2Vec2(0.0f, 0.0f));
					break;
				}
			}
		}
	}

	//TODO: Make loop through all blocks and calculate distance for light intensity
	//for (Light* light : lights) {
	//	if (glm::abs(getPosition().x - light->getPosition().x) < (light->getLight().size / 5.0f)) {
	//		_brightness = 255;
	//	}
	//	else if (glm::abs(getPosition().x - light->getPosition().x) > ((light->getLight().size * 1.5f) * (light->getLight().color.a / 255.0f))) {
	//		_brightness = 75;
	//	}
	//	else {
	//		float brightDist = 180.0f / (light->getLight().size / 5.0f - ((light->getLight().size * 1.5f) * (light->getLight().color.a / 255.0f)));
	//		_brightness = 70 + ((glm::abs(getPosition().x - light->getPosition().x) * brightDist));

	//		if (_brightness < 75) _brightness = 75;
	//		if (_brightness > 255) _brightness = 255;
	//	}
	//}
}

void Player::render(SpriteBatch & spriteBatch)
{
	glm::vec4 destRect;
	b2Body* body = _collisionBox.getBody();
	destRect.x = body->GetPosition().x - _drawDim.x / 2.0f;
	destRect.y = body->GetPosition().y - _drawDim.y / 2.0f;
	destRect.z = _drawDim.x;
	destRect.w = _drawDim.y;

	glm::vec2 velocity(body->GetLinearVelocity().x, body->GetLinearVelocity().y);

	//Calculate animation
	int tileIndex, numTiles;
	float animationSpeed = 0.2f;

	if (_onGround) {
		
		if (abs(velocity.x) > 1.0f) {
			//Running
			tileIndex = 1;
			numTiles = 6;
			animationSpeed = abs(velocity.x) * 0.025f;

			if (_moveState != PlayerMoveState::RUNNING) {
				_moveState = PlayerMoveState::RUNNING;
				_animTime = 0.0f;
			}
		}
		else {
			//Standing
			numTiles = 1;
			tileIndex = 0;
			_moveState = PlayerMoveState::STANDING;
		}
	}
	else {
		//Falling or Jumping
		numTiles = 1;
		tileIndex = 7;
		_moveState = PlayerMoveState::IN_AIR;
	}

	//Increment animation speed;
	_animTime += animationSpeed;

	//Stop animation loop
	if (_animTime > numTiles) {
		_attacking = false;
	}

	//Apply animation
	tileIndex = tileIndex + (int)_animTime % numTiles;

	glm::vec4 uvRect = _texture.getUVs(tileIndex);

	//Flip UVs if player is going left
	if (_direction == -1) {
		uvRect.x += 1.0f / _texture.dims.x;
		uvRect.z *= -1;
	}

	spriteBatch.addToBatch(destRect, uvRect, 0.0f, _texture.texture.id, Color(_brightness, _brightness, _brightness, 255), body->GetAngle());
}