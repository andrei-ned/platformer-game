#pragma once
#include "PhysicsGameObject.h"

class Player : public PhysicsGameObject
{
public:
	/// <summary> Update player velocity based on input, to be called every frame before PhysicsGameObject's update</summary>
	/// <param name="deltaTime"> Time since last frame </param>
	//void update(const sf::Time& deltaTime);
	Player();
	~Player();
private:
	bool mIsJumping;
	// Used to track time since last on ground in order to allow coyote time jumps
	float mCurrentCoyoteTime;
};

