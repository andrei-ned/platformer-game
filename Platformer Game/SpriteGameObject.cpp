#include "SpriteGameObject.h"

SpriteGameObject::SpriteGameObject() : mpTexture(nullptr), mpTextureRect(nullptr)
{
	RECT test = { 0,0,500,500 };
	mpTextureRect = &test;
}

SpriteGameObject::SpriteGameObject(ID3D11ShaderResourceView& texture)
	: SpriteGameObject()
{
	setTexture(texture);
}

SpriteGameObject::SpriteGameObject(ID3D11ShaderResourceView& texture, RECT rect)
	: SpriteGameObject(texture)
{
	setTextureRect(rect);
}

SpriteGameObject::~SpriteGameObject()
{
}

void SpriteGameObject::render(DirectX::SpriteBatch& batch)
{
	batch.Draw(mpTexture, mPos, mTextureRect ? &mTextureRect.value() : nullptr, mColor, mRotation, mOrigin, mScale, DirectX::SpriteEffects::SpriteEffects_None);
}

void SpriteGameObject::setTexture(ID3D11ShaderResourceView& texture)
{
	mpTexture = &texture;
}

void SpriteGameObject::setTexture(ID3D11ShaderResourceView& texture, RECT rect)
{
	setTexture(texture);
	setTextureRect(rect);
}

ID3D11ShaderResourceView& SpriteGameObject::getTexture() const
{
	return *mpTexture;
}

void SpriteGameObject::setTextureRect(RECT rect)
{
	mpTextureRect = &rect;
}

RECT SpriteGameObject::getTextureRect() const
{
	return *mpTextureRect;
}

//SpriteGameObject::SpriteGameObject() {
//	// Set up for base game object
//	//mDrawable = &mSprite;
//	//mTransformable = &mSprite;
//}

//SpriteGameObject::SpriteGameObject(const sf::Texture& t) : SpriteGameObject() {
//	setTexture(t);
//}
//
//SpriteGameObject::SpriteGameObject(const sf::Texture& t, const sf::IntRect& rect) : SpriteGameObject() {
//	setTexture(t, rect);
//}
//
//void SpriteGameObject::setTexture(const sf::Texture& t) {
//	mSprite.setTexture(t, true);
//}
//
//void SpriteGameObject::setTexture(const sf::Texture& t, const sf::IntRect& rect) {
//	mSprite.setTexture(t);
//	mSprite.setTextureRect(rect);
//}
//
//sf::Vector2f SpriteGameObject::getDimensions() const {
//	sf::FloatRect bounds = mSprite.getGlobalBounds();
//	return sf::Vector2f(bounds.width, bounds.height);
//}
//
//sf::FloatRect SpriteGameObject::getBounds() const {
//	return mSprite.getGlobalBounds();
//}

//bool SpriteGameObject::intersects(const SpriteGameObject& other) const {
//	//return mSprite.getGlobalBounds().intersects(other.mSprite.getGlobalBounds());
//	return false;
//}
