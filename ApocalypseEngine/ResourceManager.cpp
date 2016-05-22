#include "ResourceManager.h"

TextureCache ResourceManager::_textureCache;

GLTexture ResourceManager::getTexture(std::string texPath)
{
	GLTexture tex = _textureCache.getTexture(texPath);
	tex.filePath = texPath;
	return tex;
}