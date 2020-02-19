#pragma once
#include "GameObject.h"

// Game object that uses text
class TextGameObject : public GameObject
{
public:
	TextGameObject();
	//void setFont(sf::Font& font);
	void setCharacterPixelSize(int size);
	int getCharacterPixelSize() const;
	void setString(std::string s);
	std::string getString() const;
private:
	//sf::Text mText;
};

