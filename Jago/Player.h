#pragma once

#include "Box.h"
//#include "Light.h"

#include <ApocalypseEngine\InputManager.h>
#include <ApocalypseEngine\TileSheet.h>

enum class PlayerMoveState { STANDING, RUNNING, ATTACKING, IN_AIR };

class Player
{
public:
	Player();
	~Player();

	void init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimension, const glm::vec2& drawDim);

	void update(InputManager inputManage);
	void render(SpriteBatch& spriteBatch);

	const Box& getBox() const { return _collisionBox; }
	glm::vec2 getPosition() const { return glm::vec2(_collisionBox.getBody()->GetPosition().x, _collisionBox.getBody()->GetPosition().y); }
	glm::vec2 getDimension() const { return _dimension; }
	glm::vec2 getDrawDim() const { return _drawDim; }

	void setBrightness(GLubyte value) { _brightness = value; }

private:
	Box _collisionBox;
	glm::vec2 _dimension, _drawDim;

	TileSheet _texture;
	PlayerMoveState _moveState = PlayerMoveState::STANDING;

	bool _onGround = false;
	bool _attacking = false;
	int _direction = 1;	//< Right:1, Left:-1
	float _animTime = 0;
	GLubyte _brightness;
};