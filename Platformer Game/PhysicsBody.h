#pragma once
#include "Component.h"
#include "SimpleMath.h"
#include "Collider.h"


class PhysicsBody : public Component
{
public:
	DirectX::SimpleMath::Vector2 mVelocity;
	// Check if touching the ground (used for e.g. checking if player can jump)
	bool mIsGrounded;

	PhysicsBody(GameObject& gameObject);
	~PhysicsBody() override;

	void start() override;
	void updateLate(const float deltaTime) override;
	// If other game object is in the way of movement, sets velocity in that direction to 0
	void resolveCollision(Collider& other);
private:
	DirectX::SimpleMath::Vector2 mMaxVelDelta;
	Collider* mpCollider;
};

