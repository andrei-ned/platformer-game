#include "PhysicsBody.h"
#include "GameObject.h"
#include "GameConstants.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

PhysicsBody::PhysicsBody(GameObject& gameObject) : Component(gameObject), mMaxVelDelta(HUGE_VALF, HUGE_VALF)
{
}


PhysicsBody::~PhysicsBody()
{
}

void PhysicsBody::start()
{
	mpCollider = mpGameObject->getComponent<Collider>();
}

void PhysicsBody::updateLate(const float deltaTime) {
	Vector2 deltaVel(0, 0);
	deltaVel.x = mVelocity.x * min(deltaTime, mMaxVelDelta.x);
	deltaVel.y = mVelocity.y * min(deltaTime, mMaxVelDelta.y);
	mpGameObject->mPos += deltaVel;
	mMaxVelDelta = Vector2(HUGE_VALF, HUGE_VALF);
}

void PhysicsBody::resolveCollision(Collider& other) {
	assert(mpCollider);

	if (&other == mpCollider)
	{
		return; // Disallow collision with itself
	}

	RECTF bounds = mpCollider->getBounds();
	RECTF otherBounds = other.getBounds();
	Vector2 pos((bounds.left + bounds.right) / 2, (bounds.top + bounds.bottom) / 2);
	Vector2 otherPos((otherBounds.left + otherBounds.right) / 2, (otherBounds.top + otherBounds.bottom) / 2);

	if (other.mIsTrigger) // Trigger collision, only invoke the event
	{
		float dx = pos.x - otherPos.x;
		if ((bounds.right - bounds.left + otherBounds.right - otherBounds.left) / 2 - abs(dx) <= 0 )
			return; // Collision isn't happening

		float dy = pos.y - otherPos.y;
		if ((bounds.top - bounds.bottom + otherBounds.top - otherBounds.bottom) / 2 - abs(dy) <= 0)
			return; // Collision isn't happening

		other.mOnTrigger.invoke(*mpCollider);
	}
	else // Physics collision, constrain velocity if necessary
	{
		float scaleX = 1 / mVelocity.x;
		float scaleY = 1 / mVelocity.y;
		float signX = sign(scaleX);
		float signY = sign(scaleY);

		float nearTimeX = (otherPos.x - signX * ((bounds.right - bounds.left) + (otherBounds.right - otherBounds.left)) * 0.5f - pos.x) * scaleX;
		float nearTimeY = (otherPos.y - signY * ((bounds.bottom - bounds.top) + (otherBounds.bottom - otherBounds.top)) * 0.5f - pos.y) * scaleY;
		float farTimeX = (otherPos.x + signX * ((bounds.right - bounds.left) + (otherBounds.right - otherBounds.left)) * 0.5f - pos.x) * scaleX;
		float farTimeY = (otherPos.y + signY * ((bounds.bottom - bounds.top) + (otherBounds.bottom - otherBounds.top)) * 0.5f - pos.y) * scaleY;

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
			if (nearTimeX < 0)
				return;
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
			if (nearTimeY < 0)
				return;
			// Collision happening in direction of signY
			mMaxVelDelta.y = min(mMaxVelDelta.y, nearTimeY);
			mMaxVelDelta.y = max(mMaxVelDelta.y, 0.0f);
			if (mMaxVelDelta.y < GameConstants::COLLISION_THRESHOLD)
			{
				mVelocity.y = 0;
				if (signY > 0 && nearTimeY >= 0) // falling
				{
					mIsGrounded = true;
				}
			}
		}
	}
}
