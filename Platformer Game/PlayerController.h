#pragma once
#include "Collider.h"
#include "PhysicsBody.h"
#include "SpriteAnimator.h"

class PlayerController : public Component
{
public:
	PlayerController(GameObject& gameObject);
	~PlayerController();
	void start() override;
	void update(const float deltaTime) override;
private:
	bool mIsJumping;
	// Used to track time since last on ground in order to allow coyote time jumps
	float mCurrentCoyoteTime;
	PhysicsBody* mpPhysics;
	Sprite* mpSprite;
	SpriteAnimator* mpAnimator;
};

