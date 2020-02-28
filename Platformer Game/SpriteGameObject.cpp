#include "SpriteGameObject.h"
#include "D3DHelpers.h"

SpriteGameObject::SpriteGameObject() : mpTexture(nullptr)
{
}

SpriteGameObject::SpriteGameObject(ID3D11ShaderResourceView& texture)
	: mpTexture(&texture), mTextureRect(getMaxTextureRect(&texture))
{
}

SpriteGameObject::SpriteGameObject(ID3D11ShaderResourceView& texture, RECT rect)
	: mpTexture(&texture), mTextureRect(rect)
{
}

SpriteGameObject::~SpriteGameObject()
{
}

void SpriteGameObject::render(DirectX::SpriteBatch& batch)
{
	batch.Draw(mpTexture, mPos, &mTextureRect, mColor, mRotation, mOrigin, mScale, DirectX::SpriteEffects::SpriteEffects_None);
}

void SpriteGameObject::setTexture(ID3D11ShaderResourceView& texture)
{
	mpTexture = &texture;
	setTextureRect(getMaxTextureRect(&texture));
}

void SpriteGameObject::setTexture(ID3D11ShaderResourceView& texture, RECT rect)
{
	mpTexture = &texture;
	setTextureRect(rect);
}

ID3D11ShaderResourceView& SpriteGameObject::getTexture() const
{
	return *mpTexture;
}

void SpriteGameObject::setTextureRect(RECT rect)
{
	mTextureRect = rect;
}

RECT SpriteGameObject::getTextureRect() const
{
	return mTextureRect;
}

RECTF SpriteGameObject::getBounds() const
{
	float minX = mScale.x * (mPos.x + mOrigin.x + mTextureRect.left);
	float minY = mScale.y * (mPos.y + mOrigin.y + mTextureRect.top);
	float maxX = mScale.x * (mPos.x + mOrigin.x + mTextureRect.right);
	float maxY = mScale.y * (mPos.y + mOrigin.y + mTextureRect.bottom);
	return { minX, minY, maxX, maxY };
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
