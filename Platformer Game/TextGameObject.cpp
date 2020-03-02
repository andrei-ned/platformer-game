#include "TextGameObject.h"

TextGameObject::TextGameObject() {
	// Set up for base game object
	//mDrawable = &mText;
	//mTransformable = &mText;
}

TextGameObject::TextGameObject(SpriteFont& font) : mpFont(&font) {}

void TextGameObject::render(DirectX::SpriteBatch& batch) {
	//batch.Draw(mpTexture, mPos, &mTextureRect, mColor, mRotation, mOrigin, mScale, DirectX::SpriteEffects::SpriteEffects_None);
	mpFont->DrawString(&batch, mString.c_str(), mPos, mColor, mRotation, mScale);
}

void TextGameObject::setFont(SpriteFont& font) {
	mpFont = &font;
}

//void TextGameObject::setCharacterPixelSize(int size) {
//	//mText.setCharacterSize(size);
//}
//
//int TextGameObject::getCharacterPixelSize() const {
//	//return mText.getCharacterSize();
//	return 12;
//}
//
//void TextGameObject::setString(std::string s) {
//	//mText.setString(s);
//}
//
//std::string TextGameObject::getString() const {
//	//return mText.getString();
//	return "";
//}
