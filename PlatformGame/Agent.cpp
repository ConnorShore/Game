#include "Agent.h"

#include "Level.h"

#include <algorithm>

Agent::Agent()
{

}

void Agent::render(SpriteBatch & spriteBatch)
{
	glm::vec4 destRect(position_.x, position_.y, size_.x, size_.y);
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	spriteBatch.addToBatch(destRect, uvRect, depth_, texture_.id, color_);
}

void Agent::collideWithLevel(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePositions;

	checkTilePos(levelData, collideTilePositions, position_.x, position_.y);
	checkTilePos(levelData, collideTilePositions, position_.x + size_.x, position_.y);
	checkTilePos(levelData, collideTilePositions, position_.x, position_.y + size_.y);
	checkTilePos(levelData, collideTilePositions, position_.x + size_.x, position_.y + size_.y);

	for (int i = 0; i < collideTilePositions.size(); i++) {
		collideWithTile(collideTilePositions[i]);
	}
}

void Agent::checkTilePos(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePositions, float x, float y)
{
	glm::vec2 gridPos = glm::vec2(floor(x / (float)TILE_SIZE), floor(y / (float)TILE_SIZE));

	if (gridPos.x < 0 || gridPos.x >= levelData[0].size() ||
		gridPos.y < 0 || gridPos.y >= levelData.size()) {
		return;
	}

	if (levelData[gridPos.y][gridPos.x] != '.') {
		collideTilePositions.push_back(gridPos * TILE_SIZE + glm::vec2(TILE_SIZE / 2.0f));
	}
}

void Agent::collideWithTile(glm::vec2 tilePos)
{
	const float MIN_DIST_X = (size_.x / 2.0f) + (TILE_SIZE / 2.0f);
	const float MIN_DIST_Y = (size_.y / 2.0f) + (TILE_SIZE / 2.0f); 

	glm::vec2 centerPos(position_.x + (size_.x / 2), position_.y + (size_.y / 2));

	glm::vec2 distVec = centerPos - tilePos;

	float xDepth = MIN_DIST_X - glm::abs(distVec.x);
	float yDepth = MIN_DIST_Y - glm::abs(distVec.y);

	//True if colliding
	if (xDepth > 0 && yDepth > 0) {
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
			if (distVec.x < 0) {
				position_.x -= xDepth;
			}
			else {
				position_.x += xDepth;
			}
		}
		else {
			if (distVec.y < 0) {
				position_.y -= yDepth;
			}
			else {
				position_.y += yDepth;
			}
		}
	}
}

Agent::~Agent()
{
}
