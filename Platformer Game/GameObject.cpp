#include "GameObject.h"
#include <cassert>
#include <algorithm>
#include "Helpers.h"
#include "GameConstants.h"

GameObject::GameObject() {}

//void GameObject::render(sf::RenderWindow& window) {
//	assert(mDrawable != nullptr);
//	window.draw(*mDrawable);
//}
//
//void GameObject::setOrigin(const sf::Vector2f& off) {
//	assert(mTransformable != nullptr);
//	mTransformable->setOrigin(off);
//}
//
//sf::Vector2f GameObject::getOrigin() const {
//	assert(mTransformable != nullptr);
//	return mTransformable->getOrigin();
//}
//
//void GameObject::setScale(const sf::Vector2f& s) {
//	assert(mTransformable != nullptr);
//	mTransformable->setScale(s);
//}
//
//sf::Vector2f GameObject::getScale() const {
//	assert(mTransformable != nullptr);
//	return mTransformable->getScale();
//}
//
//void GameObject::setPos(const sf::Vector2f& pos) {
//	assert(mTransformable != nullptr);
//	mTransformable->setPosition(pos);
//}
//
//sf::Vector2f GameObject::getPos() const {
//	assert(mTransformable != nullptr);
//	return mTransformable->getPosition();
//}
//
//float GameObject::getDegrees() const {
//	assert(mTransformable != nullptr);
//	return mTransformable->getRotation();
//}
//
//void GameObject::setDegrees(float angle) {
//	assert(mTransformable != nullptr);
//	mTransformable->setRotation(angle);
//}
//
//void GameObject::addRotation(float angle) {
//	assert(mTransformable != nullptr);
//	mTransformable->rotate(angle);
//}
