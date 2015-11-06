#include "Player.h"
#include <sstream>


Player::Player(glm::vec3& position, CollisionType colType, float rotation /*0.0f*/, glm::vec3& rotationAxis /*glm::vec3(0.0f,1.0f,0.0f)*/, float scale /*1.0f*/) 
	: Actor(position, colType, rotation, rotationAxis, scale), _walkSpeed(5.0f)
{
}

void Player::initPlayer()
{
	bounds_ = createRectangleBoundsToModel();
}

void Player::update()
{
	bounds_.setPosition(getPosition());
}

Player::~Player()
{
}