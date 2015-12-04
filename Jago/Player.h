#pragma once

#include "Box.h"
#include "Torch.h"

#include <ApocalypseEngine\InputManager.h>
#include <ApocalypseEngine\TileSheet.h>

enum class PlayerMoveState { STANDING, RUNNING, ATTACKING, IN_AIR };

class Player
{
public:
	Player();
	~Player();

	void init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimension, const glm::vec2& drawDim);

	void update(InputManager inputManager, std::vector<Torch*>& lights);
	void render(SpriteBatch& spriteBatch);

	const Box& getBox() const { return _collisionBox; }
	glm::vec2 getPosition() const { return glm::vec2(_collisionBox.getBody()->GetPosition().x, _collisionBox.getBody()->GetPosition().y); }

private:
	Box _collisionBox;
	glm::vec2 _position, _dimension, _drawDim;

	TileSheet _texture;
	PlayerMoveState _moveState = PlayerMoveState::STANDING;

	bool _onGround = false;
	bool _attacking = false;
	int _direction = 1;	//< Right:1, Left:-1
	float _animTime = 0;
	GLubyte _brightness = 75;
};