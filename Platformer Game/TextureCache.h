#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>
#include "D3DHelpers.h"
#include "Constants.h"

class TextureCache : public Singleton<TextureCache>
{
public:
	TextureCache();
	~TextureCache();
	// Load texture from cache if it exists, otherwise load it from file and add it to the cache
	ID3D11ShaderResourceView* LoadTexture(const std::string& path, bool isDDS = true);
	void setDevice(ID3D11Device& device);
private:
	std::unordered_map<std::string, ID3D11ShaderResourceView*> mCache;
	ID3D11Device* mpDevice;
};

