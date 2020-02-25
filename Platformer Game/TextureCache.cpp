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

ID3D11ShaderResourceView* TextureCache::LoadTexture(ID3D11Device* pDevice, const std::string& path, bool isDDS)
{
	const std::string fullPath = Constants::TEXTURES_PATH + path;

	// Search the cache and return if already exists
	auto search = mCache.find(fullPath);
	if (search != mCache.end())
	{
		return (*search).second;
	}

	// Load texture from file
	DDS_ALPHA_MODE alpha;
	ID3D11ShaderResourceView *pT;
	std::wstring ws(fullPath.begin(), fullPath.end());
	if (isDDS)
	{
		if (CreateDDSTextureFromFile(pDevice, ws.c_str(), nullptr, &pT) != S_OK)
		{
			DBOUT("Cannot load texture at " + fullPath + "\n");
			assert(false);
		}
	}
	else
	{
		if (CreateWICTextureFromFile(pDevice, ws.c_str(), nullptr, &pT) != S_OK)
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
