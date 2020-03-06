#include "Text.h"
#include "GameObject.h"


Text::Text(GameObject& gameObject) : Component(gameObject), mOrigin(0, 0), mColor(Colors::White.v)
{
}


Text::~Text()
{
}

void Text::render(Camera& camera) {
	assert(mpFont);
	camera.drawText(mpFont, mString.c_str(), mpGameObject->mPos, mColor, mpGameObject->mRotation, mOrigin, mpGameObject->mScale, mpGameObject->mIsInWorldSpace);
}

void Text::setFont(SpriteFont& font) {
	mpFont = &font;
}
