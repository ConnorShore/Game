#include "ResourceManager.h"

TextureCache ResourceManager::_textureCache;

GLTexture ResourceManager::getTexture(std::string texPath)
{
	return _textureCache.getTexture(texPath);
}