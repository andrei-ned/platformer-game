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
	//void setCharacterPixelSize(int size);
	//int getCharacterPixelSize() const;
	//void setString(std::string s);
	//std::string getString() const;
private:
	SpriteFont *mpFont;
	//sf::Text mText;
};

