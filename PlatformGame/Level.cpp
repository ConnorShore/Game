#include "Level.h"

#include <ApocalypseEngine\Error.h>
#include <ApocalypseEngine\ResourceManager.h>

#include <glm\glm.hpp>
#include <fstream>
#include <iostream>
#include <cstdio>

Level::Level(const std::string& levelFile)
{
	std::ifstream input;
	input.open(levelFile);

	if (input.fail())
		fatalError("File does not exist: " + levelFile);

	std::string temp;

	while (std::getline(input, temp)) {
		_levelData.emplace_back(temp);
	}

	_spriteBatch.init();
	_spriteBatch.begin();

	const float TILE_SIZE = 20.0f;
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	Color white;
	white.r = 255;
	white.g = 255;
	white.b = 255;
	white.a = 255;

	for (int y = 0; y < _levelData.size(); y++) {
		for (int x = 0; x < _levelData[y].size(); x++) {
			char tile = _levelData[y][x];

			glm::vec4 destRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);

			switch (tile) {
			case 'b':
				_spriteBatch.addToBatch(destRect, uvRect, 0.0f, ResourceManager::getTexture("Textures/bullet.png").id, white);
				break;
			case '@':
				_levelData[y][x] = '.';
				_startPlayerPos.x = x * TILE_SIZE;
				_startPlayerPos.y = y * TILE_SIZE;
				break;
			case '.':
				//Do nothing
				break;
			default:
				printf("The tile %s does not exhist at (%d, %d)\n", tile, x, y);
				break;
			}
		}
	}

	_spriteBatch.end();
}

void Level::render()
{
	_spriteBatch.renderBatch();
}

Level::~Level()
{
}
