#pragma once
#include "Singleton.h"
#include <unordered_map>
#include "SpriteFont.h"


class FontCache : public Singleton<FontCache>
{
public:
	FontCache();
	~FontCache();
	// Load font from cache if it exists, otherwise load it from file and add it to the cache
	DirectX::SpriteFont* LoadSpriteFont(const std::string& path);
	void setDevice(ID3D11Device& device);
private:
	std::unordered_map<std::string, DirectX::SpriteFont*> mCache;
	ID3D11Device* mpDevice;
};

