#include "TextGameObject.h"

TextGameObject::TextGameObject() {
	// Set up for base game object
	//mDrawable = &mText;
	//mTransformable = &mText;
}

//void TextGameObject::setFont(sf::Font& font) {
//	mText.setFont(font);
//}

void TextGameObject::setCharacterPixelSize(int size) {
	//mText.setCharacterSize(size);
}

int TextGameObject::getCharacterPixelSize() const {
	//return mText.getCharacterSize();
	return 12;
}

void TextGameObject::setString(std::string s) {
	//mText.setString(s);
}

std::string TextGameObject::getString() const {
	//return mText.getString();
	return "";
}
