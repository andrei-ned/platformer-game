#include "TextGameObject.h"

TextGameObject::TextGameObject() {}

TextGameObject::TextGameObject(SpriteFont& font) : mpFont(&font) {}

void TextGameObject::render(DirectX::SpriteBatch& batch) {
	assert(mpFont);
	mpFont->DrawString(&batch, mString.c_str(), mPos, mColor, mRotation, mScale);
}

void TextGameObject::setFont(SpriteFont& font) {
	mpFont = &font;
}
