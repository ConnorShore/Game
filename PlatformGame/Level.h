#pragma once

#include <ApocalypseEngine\SpriteBatch.h>
#include <string>
#include <vector>

const float TILE_SIZE = 20.0f;

class Level
{
public:
	Level(const std::string& levelFile);
	~Level();

	void render();

	inline glm::vec2 getStartPlayerPos() const { return _startPlayerPos; }
	inline const std::vector<glm::vec2>& getStartFriendlyPos() const { return _startFriendlyPos; }
	inline const std::vector<glm::vec2>& getStartEnemyPos() const { return _startEnemyPos; }
	inline const std::vector<std::string>& getLevelData() const { return _levelData; }

private:
	glm::vec2 _startPlayerPos;
	std::vector<glm::vec2> _startFriendlyPos, _startEnemyPos;
	std::vector<std::string> _levelData;

	SpriteBatch _spriteBatch;
};

