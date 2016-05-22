#pragma once

#include "Player.h"
#include "Block.h"
#include "Tile.h"

#include <vector>
#include <string>

#include <Box2D\Box2D.h>

class TileMap
{
public:
	TileMap();
	~TileMap();

	bool saveTileMap(b2World* world, const std::string& outputFile, Player& player, std::vector<Tile>& tiles);
	bool loadTileMap(b2World* world, const std::string& inputFile, Player& player, std::vector<Tile>& tiles);

private:

};