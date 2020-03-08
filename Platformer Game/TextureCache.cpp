#include "TextureCache.h"

using namespace DirectX;

TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
	for (auto& pair : mCache)
	{
		ReleaseCOM(pair.second);
	}
	mCache.clear();
}

ID3D11ShaderResourceView* TextureCache::LoadTexture(const std::string& path, bool isDDS)
{
	assert(mpDevice);

	const std::string fullPath = Constants::TEXTURES_PATH + path;

	// Search the cache and return if already exists
	auto search = mCache.find(fullPath);
	if (search != mCache.end())
	{
		return (*search).second;
	}

	// Load texture from file
	ID3D11ShaderResourceView *pT;
	std::wstring ws(fullPath.begin(), fullPath.end());
	if (isDDS)
	{
		if (CreateDDSTextureFromFile(mpDevice, ws.c_str(), nullptr, &pT) != S_OK)
		{
			DBOUT("Cannot load texture at " + fullPath + "\n");
			assert(false);
		}
	}
	else
	{
		if (CreateWICTextureFromFile(mpDevice, ws.c_str(), nullptr, &pT) != S_OK)
		{
			DBOUT("Cannot load texture at " + fullPath + "\n");
			assert(false);
		}
	}

	// Insert into cache
	assert(pT);
	mCache.insert({ fullPath, pT });
	return pT;
}

void TextureCache::setDevice(ID3D11Device& device)
{
	mpDevice = &device;
}
