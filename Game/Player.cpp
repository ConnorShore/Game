#include "Player.h"



Player::Player()
{
}

void Player::init(Camera camera)
{
	_position = camera.getPosition();
}

void Player::update(Camera camera)
{
	_position = camera.getPosition();
}

Player::~Player()
{
}
