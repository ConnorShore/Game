#include "TextureCache.h"
#include "Loader.h"


TextureCache::TextureCache()
{
}

GLTexture TextureCache::getTexture(std::string texturePath)
{
	auto mit = _textureMap.find(texturePath);

	if (mit == _textureMap.end()) {
		GLTexture newTex = Loader::loadPNG(texturePath);
		_textureMap.insert(make_pair(texturePath, newTex));
		printf("Texture cached\n");
		return newTex;
	}

	return mit->second;
}

TextureCache::~TextureCache()
{
}
