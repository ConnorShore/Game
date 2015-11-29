#include "Player.h"
#include <SDL\SDL.h>


Player::Player()
{
}

void Player::init(glm::vec2& position)
{
	position_ = position;
	speed_ = 2.5f;
	texture_ = ResourceManager::getTexture("Textures/Player/idle_right.png");
	depth_ = 0.0f;
	setColor(255, 255, 255, 255);
	size_ = glm::vec2(20.0f, 40.0f);
}

void Player::input(InputManager & input)
{
	if (input.isKeyDown(SDLK_w)) {
		position_.y += speed_;
	}
	else if (input.isKeyDown(SDLK_s)) {
		position_.y -= speed_;
	}
	if (input.isKeyDown(SDLK_d)) {
		position_.x += speed_;
	}
	else if (input.isKeyDown(SDLK_a)) {
		position_.x -= speed_;
	}
}

void Player::update()
{

}

Player::~Player()
{
}
