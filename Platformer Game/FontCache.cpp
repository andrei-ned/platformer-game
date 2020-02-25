#include "FontCache.h"
#include "Constants.h"


FontCache::FontCache()
{
}

FontCache::~FontCache()
{
	for (auto& pair : mCache)
	{
		delete pair.second;
	}
	mCache.clear();
}

SpriteFont* FontCache::LoadSpriteFont(ID3D11Device* pDevice, const std::string& path)
{
	const std::string fullPath = Constants::FONTS_PATH + path;

	// Search the cache and return if already exists
	auto search = mCache.find(fullPath);
	if (search != mCache.end())
	{
		return (*search).second;
	}

	// Load font from file
	std::wstring ws(fullPath.begin(), fullPath.end());
	SpriteFont* font = new SpriteFont(pDevice, ws.c_str());

	// Insert into cache
	assert(font);
	mCache.insert({ fullPath, font });
	return font;
}
