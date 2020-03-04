#pragma once
#include "SpriteGameObject.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
 
// Implements physics on top of SpriteGameObject
class PhysicsGameObject : public SpriteGameObject
{
public:
	Vector2 mVelocity;
	PhysicsGameObject();
	/// <summary> To be called every frame to apply velocity</summary>
	/// <param name="deltaTime"> Time since last frame </param>
	void update(const float deltaTime);
	// If other game object is in the way of movement, sets velocity in that direction to 0
	void resolveCollision(const SpriteGameObject& other);
	// Check if touching the ground (used for e.g. checking if player can jump)
	bool isGrounded() const;
protected:
	bool mIsGrounded;
private:
	Vector2 mMaxVelDelta;
};
