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

	//const scaleX = 1.0 / delta.x;
	//const scaleY = 1.0 / delta.y;
	//const signX = sign(scaleX);
	//const signY = sign(scaleY);
	float scaleX = 1 / mVelocity.x;
	float scaleY = 1 / mVelocity.y;
	float signX = sign(scaleX);
	float signY = sign(scaleY);

	//const nearTimeX = (this.pos.x - signX * (this.half.x + paddingX) - pos.x) * scaleX;
	//const nearTimeY = (this.pos.y - signY * (this.half.y + paddingY) - pos.y) * scaleY;
	//const farTimeX = (this.pos.x + signX * (this.half.x + paddingX) - pos.x) * scaleX;
	//const farTimeY = (this.pos.y + signY * (this.half.y + paddingY) - pos.y) * scaleY;
	float nearTimeX = (otherPos.x - signX * (bounds.width  + otherBounds.width)  * 0.5f - pos.x) * scaleX;
	float nearTimeY = (otherPos.y - signY * (bounds.height + otherBounds.height) * 0.5f - pos.y) * scaleY;
	float farTimeX  = (otherPos.x + signX * (bounds.width  + otherBounds.width)  * 0.5f - pos.x) * scaleX;
	float farTimeY  = (otherPos.y + signY * (bounds.height + otherBounds.height) * 0.5f - pos.y) * scaleY;

	//if (nearTimeX > farTimeY || nearTimeY > farTimeX) {
	//	return null;
	//}
	if (nearTimeX > farTimeY || nearTimeY > farTimeX) 
	{
		return; // collision isn't happening
	}

	//const nearTime = nearTimeX > nearTimeY ? nearTimeX : nearTimeY;
	//const farTime = farTimeX < farTimeY ? farTimeX : farTimeY;
	float nearTime = std::max(nearTimeX, nearTimeY);
	float farTime = std::min(farTimeX, farTimeY);

	if (farTime <= 0)
	{
		return; // collision isn't happening
	}

	//const hit = new Hit(this);
	//hit.time = clamp(nearTime, 0, 1);
	//if (nearTimeX > nearTimeY) {
	//	hit.normal.x = -signX;
	//	hit.normal.y = 0;
	//}
	//else {
	//	hit.normal.x = 0;
	//	hit.normal.y = -signY;
	//}
	//hit.delta.x = (1.0 - hit.time) * -delta.x;
	//hit.delta.y = (1.0 - hit.time) * -delta.y;
	//hit.pos.x = pos.x + delta.x * hit.time;
	//hit.pos.y = pos.y + delta.y * hit.time;
	//return hit;
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

	//sf::FloatRect bounds = getBounds();
	//sf::FloatRect otherBounds = other.getBounds();
	//sf::FloatRect intersection;

	//if (bounds.intersects(otherBounds, intersection)) // There is a collision, may have to constrain velocity
	//{
	//	sf::Vector2f intersectionPos(intersection.left + intersection.width / 2, intersection.top + intersection.height / 2);
	//	//sf::Vector2f pos(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
	//	sf::Vector2f otherPos(otherBounds.left + otherBounds.width / 2, otherBounds.top + otherBounds.height / 2);
	//	sf::Vector2f direction(otherPos - intersectionPos);

	//	bool constrainX = false;
	//	bool constrainY = false;

	//	// Check if moving towards other object
	//	float signX = sign(mVelocity.x);
	//	float signY = sign(mVelocity.y);
	//	if (sign(direction.x) == signX)
	//	{
	//		constrainX = true;
	//	}
	//	if (sign(direction.y) == signY)
	//	{
	//		constrainY = true;
	//	}

	//	// Only constrain smallest distance
	//	if (constrainX && constrainY)
	//	{
	//		//float xDist = abs(intersectionPos.x - otherPos.x + signX * otherBounds.width * 0.5f);
	//		//float yDist = abs(intersectionPos.y - otherPos.y + signY * otherBounds.height * 0.5f);
	//		float xDist = otherBounds.width * 0.5f - abs(intersectionPos.x - otherPos.x);
	//		float yDist = otherBounds.height * 0.5f - abs(intersectionPos.y - otherPos.y);
	//		if (xDist < yDist)
	//		{
	//			constrainY = false;
	//		}
	//		else
	//		{
	//			constrainX = false;
	//		}
	//	}

	//	// Apply constraint
	//	if (constrainX)
	//	{
	//		mVelocity.x = 0;
	//		//setPos(getPos() - signX * sf::Vector2f(intersection.width, 0));
	//		//std::cout << "X\n";
	//	}
	//	if (constrainY)
	//	{
	//		mIsGrounded = mVelocity.y >= 0;
	//		mVelocity.y = 0;
	//		//setPos(getPos() - signY * sf::Vector2f(0, intersection.height));
	//		//std::cout << "Y\n";
	//	}
	//}
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
