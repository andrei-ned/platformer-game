#include "Text.h"
#include "GameObject.h"


Text::Text(GameObject& gameObject) : Component(gameObject), mOrigin(0, 0), mColor(Colors::White.v)
{
}


Text::~Text()
{
}

void Text::render(DirectX::SpriteBatch& batch) {
	assert(mpFont);
	mpFont->DrawString(&batch, mString.c_str(), mpGameObject->mPos, mColor, mpGameObject->mRotation, mpGameObject->mScale);
}

void Text::setFont(SpriteFont& font) {
	mpFont = &font;
}
