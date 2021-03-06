#include "PlayerController.h"
#include "GameObject.h"
#include "GameConstants.h"
#include "Keyboard.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


PlayerController::PlayerController(GameObject& gameObject) : Component(gameObject)
{
}


PlayerController::~PlayerController()
{
}

void PlayerController::start()
{
	mpPhysics = mpGameObject->getComponent<PhysicsBody>();
	mpSprite = mpGameObject->getComponent<Sprite>();
	mpAnimator = mpGameObject->getComponent<SpriteAnimator>();
}

void PlayerController::update(const float deltaTime)
{
	// Animations
	if (mpPhysics->mVelocity.x > 0)
		mpSprite->mSpriteEffects = SpriteEffects_None;
	if (mpPhysics->mVelocity.x < 0)
		mpSprite->mSpriteEffects = SpriteEffects_FlipHorizontally;

	if (mpPhysics->mIsGrounded)
	{
		if (abs(mpPhysics->mVelocity.x) > 25.0f)
		{
			mpAnimator->playAnimation("Run");
			mpAnimator->setSpeed(min(20.0f / abs(mpPhysics->mVelocity.x), 0.075f));
		}
		else
		{
			mpAnimator->playAnimation("Idle");
		}
	}
	else
	{
		mpAnimator->playAnimation(mpPhysics->mVelocity.y > 0 ? "Fall" : "Jump");
	}


	auto keyboardState = Keyboard::Get().GetState();

	Vector2 playerVel(mpPhysics->mVelocity);

	// Apply gravity
	playerVel.y += GameConstants::GRAVITY * deltaTime;
	playerVel.y = min(playerVel.y, GameConstants::MAX_FALL_SPEED);

	float moveInput = 0;

	// Apply horizontal acceleration from inputs
	if (keyboardState.Left)
	{
		moveInput -= 1;
		playerVel.x -= GameConstants::PLAYER_MOVE_ACCELERATION * deltaTime;
		playerVel.x = max(playerVel.x, -GameConstants::PLAYER_MAX_MOVE_SPEED);
	}
	if (keyboardState.Right)
	{
		moveInput += 1;
		playerVel.x += GameConstants::PLAYER_MOVE_ACCELERATION * deltaTime;
		playerVel.x = min(playerVel.x, GameConstants::PLAYER_MAX_MOVE_SPEED);
	}

	if (moveInput == 0 || sign(playerVel.x) != sign(moveInput))
	{
		playerVel.x *= std::powf(GameConstants::PLAYER_DECELARATION_MULTIPLIER, deltaTime);
	}

	// Handle jumping
	if (mpPhysics->mIsGrounded)
	{
		mCurrentCoyoteTime = 0;
	}
	else
	{
		mCurrentCoyoteTime += deltaTime;
	}
	if (mpPhysics->mIsGrounded || mCurrentCoyoteTime < GameConstants::PLAYER_COYOTE_TIME)
	{
		if (playerVel.y > 0) 
			mpPhysics->mIsGrounded = false;
		if (keyboardState.Up)
		{
			mCurrentCoyoteTime += GameConstants::PLAYER_COYOTE_TIME;
			playerVel.y = GameConstants::PLAYER_JUMP_SPEED;
			mpPhysics->mIsGrounded = false;
			mIsJumping = true;
		}
	}

	// Jump higher if key is held
	if (mIsJumping)
	{
		mIsJumping = keyboardState.Up;
	}
	else
	{
		playerVel.y = max(playerVel.y, GameConstants::PLAYER_MIN_JUMP_SPEED);
	}

	mpPhysics->mVelocity = playerVel;
}
