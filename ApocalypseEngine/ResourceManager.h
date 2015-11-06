#pragma once

#include "TextureCache.h"

class ResourceManager
{
public:
	static GLTexture getTexture(std::string texPath);

private:
	static TextureCache _textureCache;
};

