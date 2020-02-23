#pragma once
#include "Singleton.h"

class TextureCache : public Singleton<TextureCache>
{
public:
	TextureCache();
	~TextureCache();
	void test() {};
};

