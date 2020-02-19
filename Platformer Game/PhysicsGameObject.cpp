#include "PhysicsGameObject.h"

PhysicsGameObject::PhysicsGameObject() {}

//void PhysicsGameObject::update(const sf::Time& deltaTime) {
//	float dt = deltaTime.asSeconds();
//	sf::Vector2f deltaVel(0, 0);
//	deltaVel.x = mVelocity.x * std::min(dt, mMaxVelDelta.x);
//	deltaVel.y = mVelocity.y * std::min(dt, mMaxVelDelta.y);
//	mSprite.move(deltaVel);
//	mMaxVelDelta = sf::Vector2f(HUGE_VALF, HUGE_VALF);
//}
//
//sf::Vector2f PhysicsGameObject::getVelocity() const {
//	return mVelocity;
//}
//
//void PhysicsGameObject::setVelocity(const sf::Vector2f& v) {
//	mVelocity = v;
//}

void PhysicsGameObject::resolveCollision(const SpriteGameObject& other) {
	//sf::FloatRect bounds = getBounds();
	//sf::FloatRect otherBounds = other.getBounds();
	//sf::Vector2f pos(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
	//sf::Vector2f otherPos(otherBounds.left + otherBounds.width / 2, otherBounds.top + otherBounds.height / 2);

	//float scaleX = 1 / mVelocity.x;
	//float scaleY = 1 / mVelocity.y;
	//float signX = sign(scaleX);
	//float signY = sign(scaleY);

	//float nearTimeX = (otherPos.x - signX * (bounds.width  + otherBounds.width)  * 0.5f - pos.x) * scaleX;
	//float nearTimeY = (otherPos.y - signY * (bounds.height + otherBounds.height) * 0.5f - pos.y) * scaleY;
	//float farTimeX  = (otherPos.x + signX * (bounds.width  + otherBounds.width)  * 0.5f - pos.x) * scaleX;
	//float farTimeY  = (otherPos.y + signY * (bounds.height + otherBounds.height) * 0.5f - pos.y) * scaleY;

	//if (nearTimeX > farTimeY || nearTimeY > farTimeX) 
	//{
	//	return; // Collision isn't happening
	//}

	//if (std::min(farTimeX, farTimeY) <= 0)
	//{
	//	return; // Collision isn't happening
	//}

	//if (nearTimeX > nearTimeY)
	//{
	//	// Collision happening in direction of signX
	//	mMaxVelDelta.x = std::min(mMaxVelDelta.x, nearTimeX);
	//	mMaxVelDelta.x = std::max(mMaxVelDelta.x, 0.0f);
	//	if (mMaxVelDelta.x < GameConstants::COLLISION_THRESHOLD)
	//	{
	//		mVelocity.x = 0;
	//	}
	//}
	//else
	//{
	//	// Collision happening in direction of signY
	//	mMaxVelDelta.y = std::min(mMaxVelDelta.y, nearTimeY);
	//	mMaxVelDelta.y = std::max(mMaxVelDelta.y, 0.0f);
	//	if (mMaxVelDelta.y < GameConstants::COLLISION_THRESHOLD)
	//	{
	//		mVelocity.y = 0;
	//		if (signY > 0) // falling
	//		{
	//			mIsGrounded = true;
	//		}
	//	}
	//}
}

bool PhysicsGameObject::isGrounded() const {
	return mIsGrounded;
}
