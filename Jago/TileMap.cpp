#include "TileMap.h"

#include <ApocalypseEngine\Error.h>
#include <ApocalypseEngine\ResourceManager.h>

#include <fstream>

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
}

bool TileMap::saveTileMap(b2World* world, const std::string& outputFile, Player & player, std::vector<Tile>& tiles)
{
	std::ofstream file(outputFile);
	if (file.fail()) {
		fatalError("Failed to create file: " + outputFile);
		return false;
	}

	file << player.getPosition().x << "\t" << player.getPosition().y << "\t"
		<< player.getDimension().x << "\t" << player.getDimension().y << "\t"
		<< player.getDrawDim().x << "\t" << player.getDrawDim().y << "\n";

	file  << tiles.size() << "\n";
	
	for (auto& t : tiles) {
		file << t.position.x << "\t" << t.position.y << "\t"
			<< t.texture.filePath << "\t" << t.depth << "\t" << t.isCollidable << "\n";
	}

	return true;
}

bool TileMap::loadTileMap(b2World* world, const std::string& inputFile, Player & player, std::vector<Tile>& tiles)
{
	std::ifstream file(inputFile);

	if (file.fail()) {
		fatalError("Failed to open file: " + inputFile);
		return false;
	}

	{
		//player
		glm::vec2 pos, dim, drawDim;

		file >> pos.x >> pos.y >> dim.x >> dim.y >> drawDim.x >> drawDim.y;
		player.init(world, pos, dim, drawDim);
	}

	{
		//Tiles
		size_t numTiles;
		file >> numTiles;

		glm::vec2 pos;
		std::string texFile;
		GLTexture texture;
		bool collide;
		float depth;

		for (int i = 0; i < numTiles; i++) {
			file >> pos.x >> pos.y >> texFile >> depth >> collide;
			texture = ResourceManager::getTexture(texFile);
			tiles.emplace_back();
			tiles.back().init(pos, texture, depth, collide);
		}
	}

	return true;
}