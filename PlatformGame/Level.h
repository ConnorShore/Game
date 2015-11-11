#pragma once

#include <ApocalypseEngine\SpriteBatch.h>
#include <string>
#include <vector>

class Level
{
public:
	Level(const std::string& levelFile);
	~Level();

	void render();

	glm::vec2 getStartPlayerPos() const { return _startPlayerPos; }
	const std::vector<glm::vec2>& getStartFriendlyPos() const { return _startFriendlyPos; }
	const std::vector<glm::vec2>& getStartEnemyPos() const { return _startEnemyPos; }

private:
	glm::vec2 _startPlayerPos;
	std::vector<glm::vec2> _startFriendlyPos, _startEnemyPos;
	std::vector<std::string> _levelData;
	SpriteBatch _spriteBatch;
};

