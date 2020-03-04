#pragma once
#include "GameObject.h"
#include <SpriteFont.h>

// Game object that uses text
class TextGameObject : public GameObject
{
public:
	std::string mString;
	TextGameObject();
	TextGameObject(SpriteFont& font);
	void render(DirectX::SpriteBatch& batch);
	void setFont(SpriteFont& font);
private:
	SpriteFont *mpFont;
};

