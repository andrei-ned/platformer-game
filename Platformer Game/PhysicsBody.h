#pragma once
#include "Component.h"
#include "SimpleMath.h"
#include "Collider.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class PhysicsBody : public Component
{
public:
	Vector2 mVelocity;
	// Check if touching the ground (used for e.g. checking if player can jump)
	bool mIsGrounded;
	PhysicsBody(GameObject& gameObject);
	~PhysicsBody();
	void start() override;
	void updateLate(const float deltaTime) override;
	// If other game object is in the way of movement, sets velocity in that direction to 0
	void resolveCollision(const Collider& other);
private:
	Vector2 mMaxVelDelta;
	Collider* mpCollider;
};
