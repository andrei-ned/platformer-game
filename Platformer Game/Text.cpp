#include "Text.h"
#include "GameObject.h"


Text::Text(GameObject& gameObject) : Component(gameObject), mOrigin(0, 0), mScale(1, 1), mColor(Colors::White.v)
{
}


Text::~Text()
{
}

void Text::render(Camera& camera) {
	assert(mpFont);
	camera.drawText(mpFont, mString.c_str(), mpGameObject->mPos, mColor, mpGameObject->mRotation, mOrigin, mpGameObject->mScale * mScale, mpGameObject->mIsInWorldSpace, mSpriteEffects);
}

void Text::setFont(SpriteFont& font) {
	mpFont = &font;
}

Vector2 Text::getDimensions() const
{
	return mpFont->MeasureString(mString.c_str());
}
