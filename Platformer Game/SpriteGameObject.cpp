#include "SpriteGameObject.h"

SpriteGameObject::SpriteGameObject() {
	// Set up for base game object
	//mDrawable = &mSprite;
	//mTransformable = &mSprite;
}

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

bool SpriteGameObject::intersects(const SpriteGameObject& other) const {
	//return mSprite.getGlobalBounds().intersects(other.mSprite.getGlobalBounds());
	return false;
}
