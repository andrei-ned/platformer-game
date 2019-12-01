#include "GameObject.h"
#include <cassert>

#pragma region GameObject
GameObject::GameObject() {}

void GameObject::render(sf::RenderWindow& window) {
	assert(mDrawable != nullptr);
	window.draw(*mDrawable);
}

void GameObject::setOrigin(const sf::Vector2f& off) {
	assert(mTransformable != nullptr);
	mTransformable->setOrigin(off);
}

sf::Vector2f GameObject::getOrigin() const {
	assert(mTransformable != nullptr);
	return mTransformable->getOrigin();
}

void GameObject::setScale(const sf::Vector2f& s) {
	assert(mTransformable != nullptr);
	mTransformable->setScale(s);
}

sf::Vector2f GameObject::getScale() const {
	assert(mTransformable != nullptr);
	return mTransformable->getScale();
}

void GameObject::setPos(const sf::Vector2f& pos) {
	assert(mTransformable != nullptr);
	mTransformable->setPosition(pos);
}

sf::Vector2f GameObject::getPos() const {
	assert(mTransformable != nullptr);
	return mTransformable->getPosition();
}

float GameObject::getDegrees() const {
	assert(mTransformable != nullptr);
	return mTransformable->getRotation();
}

void GameObject::setDegrees(float angle) {
	assert(mTransformable != nullptr);
	mTransformable->setRotation(angle);
}

void GameObject::addRotation(float angle) {
	assert(mTransformable != nullptr);
	mTransformable->rotate(angle);
}
#pragma endregion

#pragma region SpriteGameObject
SpriteGameObject::SpriteGameObject() {
	// Set up for base game object
	mDrawable = &mSprite;
	mTransformable = &mSprite;
}

SpriteGameObject::SpriteGameObject(const sf::Texture& t) : SpriteGameObject() {
	setTexture(t);
}

SpriteGameObject::SpriteGameObject(const sf::Texture& t, const sf::IntRect& rect) : SpriteGameObject() {
	setTexture(t, rect);
}

void SpriteGameObject::setTexture(const sf::Texture& t) {
	mSprite.setTexture(t, true);
}

void SpriteGameObject::setTexture(const sf::Texture& t, const sf::IntRect& rect) {
	mSprite.setTexture(t);
	mSprite.setTextureRect(rect);
}
#pragma endregion

#pragma region PhysicsGameObject
PhysicsGameObject::PhysicsGameObject() {}

void PhysicsGameObject::update(const sf::Time& deltaTime) {
	mSprite.move(mVelocity * deltaTime.asSeconds());
}

sf::Vector2f PhysicsGameObject::getVelocity() const {
	return mVelocity;
}

void PhysicsGameObject::setVelocity(const sf::Vector2f& v) {
	mVelocity = v;
}

bool PhysicsGameObject::checkForCollision(const PhysicsGameObject& other) const {
	return mSprite.getGlobalBounds().intersects(other.mSprite.getGlobalBounds());
}

sf::Vector2f PhysicsGameObject::getDimensions() const {
	sf::FloatRect bounds = mSprite.getGlobalBounds();
	return sf::Vector2f(bounds.width, bounds.height);
}

sf::FloatRect PhysicsGameObject::getBounds() const {
	return mSprite.getGlobalBounds();
}
#pragma endregion

#pragma region TextGameObject
TextGameObject::TextGameObject() {
	// Set up for base game object
	mDrawable = &mText;
	mTransformable = &mText;
}

void TextGameObject::setFont(sf::Font& font) {
	mText.setFont(font);
}

void TextGameObject::setCharacterPixelSize(int size) {
	mText.setCharacterSize(size);
}

int TextGameObject::getCharacterPixelSize() const {
	return mText.getCharacterSize();
}

void TextGameObject::setString(std::string s) {
	mText.setString(s);
}

std::string TextGameObject::getString() const {
	return mText.getString();
}
#pragma endregion
