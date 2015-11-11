#include "Agent.h"



Agent::Agent()
{

}

void Agent::render(SpriteBatch & spriteBatch)
{
	glm::vec4 destRect(position_.x, position_.y, size_.x, size_.y);
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	spriteBatch.addToBatch(destRect, uvRect, depth_, texture_.id, color_);
}

Agent::~Agent()
{
}
