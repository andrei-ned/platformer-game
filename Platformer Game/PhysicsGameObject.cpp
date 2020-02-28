#include "PhysicsGameObject.h"
#include <algorithm>
#include "GameConstants.h"

PhysicsGameObject::PhysicsGameObject() : mMaxVelDelta(Vector2(HUGE_VALF, HUGE_VALF)) {}

void PhysicsGameObject::update(const float deltaTime) {
	Vector2 deltaVel(0, 0);
	deltaVel.x = mVelocity.x * min(deltaTime, mMaxVelDelta.x);
	deltaVel.y = mVelocity.y * min(deltaTime, mMaxVelDelta.y);
	mPos += deltaVel;
	mMaxVelDelta = Vector2(HUGE_VALF, HUGE_VALF);
}

void PhysicsGameObject::resolveCollision(const SpriteGameObject& other) {
	//sf::FloatRect bounds = getBounds();
	RECTF bounds = getBounds();
	//sf::FloatRect otherBounds = other.getBounds();
	RECTF otherBounds = other.getBounds();
	//sf::Vector2f pos(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
	Vector2 pos((bounds.left + bounds.right) / 2, (bounds.top + bounds.bottom) / 2);
	//sf::Vector2f otherPos(otherBounds.left + otherBounds.width / 2, otherBounds.top + otherBounds.height / 2);
	Vector2 otherPos((otherBounds.left + otherBounds.right) / 2, (otherBounds.top + otherBounds.bottom) / 2);

	float scaleX = 1 / mVelocity.x;
	float scaleY = 1 / mVelocity.y;
	float signX = sign(scaleX);
	float signY = sign(scaleY);

	//float nearTimeX = (otherPos.x - signX * (bounds.width  + otherBounds.width)  * 0.5f - pos.x) * scaleX;
	float nearTimeX = (otherPos.x - signX * ((bounds.right - bounds.left)  + (otherBounds.right - otherBounds.left))  * 0.5f - pos.x) * scaleX;
	//float nearTimeY = (otherPos.y - signY * (bounds.height + otherBounds.height) * 0.5f - pos.y) * scaleY;
	float nearTimeY = (otherPos.y - signY * ((bounds.bottom - bounds.top) + (otherBounds.bottom - otherBounds.top)) * 0.5f - pos.y) * scaleY;
	//float farTimeX  = (otherPos.x + signX * (bounds.width  + otherBounds.width)  * 0.5f - pos.x) * scaleX;
	float farTimeX  = (otherPos.x + signX * ((bounds.right - bounds.left) + (otherBounds.right - otherBounds.left))  * 0.5f - pos.x) * scaleX;
	//float farTimeY  = (otherPos.y + signY * (bounds.height + otherBounds.height) * 0.5f - pos.y) * scaleY;
	float farTimeY  = (otherPos.y + signY * ((bounds.bottom - bounds.top) + (otherBounds.bottom - otherBounds.top)) * 0.5f - pos.y) * scaleY;

	if (nearTimeX > farTimeY || nearTimeY > farTimeX) 
	{
		return; // Collision isn't happening
	}

	if (min(farTimeX, farTimeY) <= 0)
	{
		return; // Collision isn't happening
	}

	if (nearTimeX > nearTimeY)
	{
		// Collision happening in direction of signX
		mMaxVelDelta.x = min(mMaxVelDelta.x, nearTimeX);
		mMaxVelDelta.x = max(mMaxVelDelta.x, 0.0f);
		if (mMaxVelDelta.x < GameConstants::COLLISION_THRESHOLD)
		{
			mVelocity.x = 0;
		}
	}
	else
	{
		// Collision happening in direction of signY
		mMaxVelDelta.y = min(mMaxVelDelta.y, nearTimeY);
		mMaxVelDelta.y = max(mMaxVelDelta.y, 0.0f);
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
