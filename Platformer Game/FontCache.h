#pragma once
#include "Singleton.h"
#include <unordered_map>
#include "SpriteFont.h"

using namespace DirectX;

class FontCache : public Singleton<FontCache>
{
public:
	FontCache();
	~FontCache();
	// Load font from cache if it exists, otherwise load it from file and add it to the cache
	SpriteFont* LoadSpriteFont(ID3D11Device* pDevice, const std::string& path);
private:
	std::unordered_map<std::string, SpriteFont*> mCache;
};

