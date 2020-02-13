#include "GameObject.h"
#include <cassert>
#include <algorithm>
#include "Helpers.h"
#include "GameConstants.h"

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

sf::Vector2f SpriteGameObject::getDimensions() const {
	sf::FloatRect bounds = mSprite.getGlobalBounds();
	return sf::Vector2f(bounds.width, bounds.height);
}

sf::FloatRect SpriteGameObject::getBounds() const {
	return mSprite.getGlobalBounds();
}

bool SpriteGameObject::intersects(const SpriteGameObject& other) const {
	return mSprite.getGlobalBounds().intersects(other.mSprite.getGlobalBounds());
}
#pragma endregion

#pragma region PhysicsGameObject
PhysicsGameObject::PhysicsGameObject() {}

void PhysicsGameObject::update(const sf::Time& deltaTime) {
	float dt = deltaTime.asSeconds();
	sf::Vector2f deltaVel(0, 0);
	deltaVel.x = mVelocity.x * std::min(dt, mMaxVelDelta.x);
	deltaVel.y = mVelocity.y * std::min(dt, mMaxVelDelta.y);
	mSprite.move(deltaVel);
	mMaxVelDelta = sf::Vector2f(HUGE_VALF, HUGE_VALF);
}

sf::Vector2f PhysicsGameObject::getVelocity() const {
	return mVelocity;
}

void PhysicsGameObject::setVelocity(const sf::Vector2f& v) {
	mVelocity = v;
}

void PhysicsGameObject::resolveCollision(const SpriteGameObject& other) {
	sf::FloatRect bounds = getBounds();
	sf::FloatRect otherBounds = other.getBounds();
	sf::Vector2f pos(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
	sf::Vector2f otherPos(otherBounds.left + otherBounds.width / 2, otherBounds.top + otherBounds.height / 2);

	float scaleX = 1 / mVelocity.x;
	float scaleY = 1 / mVelocity.y;
	float signX = sign(scaleX);
	float signY = sign(scaleY);

	float nearTimeX = (otherPos.x - signX * (bounds.width  + otherBounds.width)  * 0.5f - pos.x) * scaleX;
	float nearTimeY = (otherPos.y - signY * (bounds.height + otherBounds.height) * 0.5f - pos.y) * scaleY;
	float farTimeX  = (otherPos.x + signX * (bounds.width  + otherBounds.width)  * 0.5f - pos.x) * scaleX;
	float farTimeY  = (otherPos.y + signY * (bounds.height + otherBounds.height) * 0.5f - pos.y) * scaleY;

	if (nearTimeX > farTimeY || nearTimeY > farTimeX) 
	{
		return; // Collision isn't happening
	}

	if (std::min(farTimeX, farTimeY) <= 0)
	{
		return; // Collision isn't happening
	}

	if (nearTimeX > nearTimeY)
	{
		// Collision happening in direction of signX
		mMaxVelDelta.x = std::min(mMaxVelDelta.x, nearTimeX);
		mMaxVelDelta.x = std::max(mMaxVelDelta.x, 0.0f);
		if (mMaxVelDelta.x < GameConstants::COLLISION_THRESHOLD)
		{
			mVelocity.x = 0;
		}
	}
	else
	{
		// Collision happening in direction of signY
		mMaxVelDelta.y = std::min(mMaxVelDelta.y, nearTimeY);
		mMaxVelDelta.y = std::max(mMaxVelDelta.y, 0.0f);
		if (mMaxVelDelta.y < GameConstants::COLLISION_THRESHOLD)
		{
			mVelocity.y = 0;
			if (signY > 0) // falling
			{
				mIsGrounded = true;
			}
		}
	}
}

bool PhysicsGameObject::isGrounded() const {
	return mIsGrounded;
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
