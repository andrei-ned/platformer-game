#include "GameObject.h"
#include <cassert>
#include <algorithm>

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
	float delta = deltaTime.asSeconds();
	if (mMaxTimeSet)
	{
		delta = std::max(delta, mMaxVelocityTime);
	}
	mSprite.move(mVelocity * delta);
	mMaxTimeSet = false;
}

sf::Vector2f PhysicsGameObject::getVelocity() const {
	return mVelocity;
}

void PhysicsGameObject::setVelocity(const sf::Vector2f& v) {
	mVelocity = v;
}

sf::Vector2f PhysicsGameObject::getDimensions() const {
	sf::FloatRect bounds = mSprite.getGlobalBounds();
	return sf::Vector2f(bounds.width, bounds.height);
}

sf::FloatRect PhysicsGameObject::getBounds() const {
	return mSprite.getGlobalBounds();
}

bool PhysicsGameObject::checkForCollision(const PhysicsGameObject& other) const {
	return mSprite.getGlobalBounds().intersects(other.mSprite.getGlobalBounds());
}

void PhysicsGameObject::resolveCollision(const PhysicsGameObject& other) {
	//sweep.hit = this.intersectSegment(box.pos, delta, box.half.x, box.half.y);

	mMaxTimeSet = true;

	sf::Vector2f pos = getPos();
	sf::FloatRect bounds = getBounds();

	//const scaleX = 1.0 / delta.x;
	//const scaleY = 1.0 / delta.y;
	//const signX = sign(scaleX);
	//const signY = sign(scaleY);
	//const nearTimeX = (this.pos.x - signX * (this.half.x + paddingX) - pos.x) * scaleX;
	//const nearTimeY = (this.pos.y - signY * (this.half.y + paddingY) - pos.y) * scaleY;
	//const farTimeX = (this.pos.x + signX * (this.half.x + paddingX) - pos.x) * scaleX;
	//const farTimeY = (this.pos.y + signY * (this.half.y + paddingY) - pos.y) * scaleY;

	float nearX;
	float nearY;
	float farX;
	float farY;

	if (mVelocity.x > 0)
	{
		nearX = bounds.left;
		farX = bounds.left + bounds.width;
	}
	else
	{
		nearX = bounds.left + bounds.width;
		farX = bounds.left;
	}
	if (mVelocity.y > 0)
	{
		nearY = bounds.top;
		farY = bounds.top + bounds.height;
	}
	else
	{
		nearY = bounds.top + bounds.height;
		farY = bounds.top;
	}


	//if (sweep.hit) {
	//	sweep.time = clamp(sweep.hit.time - EPSILON, 0, 1);
	//	sweep.pos.x = box.pos.x + delta.x * sweep.time;
	//	sweep.pos.y = box.pos.y + delta.y * sweep.time;
	//	const direction = delta.clone();
	//	direction.normalize();
	//	sweep.hit.pos.x = clamp(
	//		sweep.hit.pos.x + direction.x * box.half.x,
	//		this.pos.x - this.half.x, this.pos.x + this.half.x);
	//	sweep.hit.pos.y = clamp(
	//		sweep.hit.pos.y + direction.y * box.half.y,
	//		this.pos.y - this.half.y, this.pos.y + this.half.y);
	//}
	//else {
	//	sweep.pos.x = box.pos.x + delta.x;
	//	sweep.pos.y = box.pos.y + delta.y;
	//	sweep.time = 1;
	//}
	//return sweep;
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
