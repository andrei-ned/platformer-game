#pragma once
#include "SpriteGameObject.h"

// Implements physics on top of SpriteGameObject
class PhysicsGameObject : public SpriteGameObject
{
public:
	PhysicsGameObject();
	/// <summary> To be called every frame to apply velocity</summary>
	/// <param name="deltaTime"> Time since last frame </param>
	//void update(const sf::Time& deltaTime);
	//sf::Vector2f getVelocity() const;
	//void setVelocity(const sf::Vector2f& v);
	// If other game object is in the way of movement, sets velocity in that direction to 0
	void resolveCollision(const SpriteGameObject& other);
	// Check if touching the ground (used for e.g. checking if player can jump)
	bool isGrounded() const;
	//sf::Vector2f mMaxVelDelta;
protected:
	bool mIsGrounded;
private:
	//sf::Vector2f mVelocity;
};
