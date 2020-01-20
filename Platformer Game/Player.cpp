#include "Player.h"
#include "GameConstants.h"
#include "Helpers.h"

Player::Player() {
}


Player::~Player() {
}

void Player::update(const sf::Time& deltaTime) {
	float delta = deltaTime.asSeconds();
	sf::Vector2f playerVel(getVelocity());

	// Apply gravity
	playerVel.y += GameConstants::GRAVITY * delta;
	playerVel.y = std::min(playerVel.y, GameConstants::MAX_FALL_SPEED);

	float moveInput = 0;

	// Apply horizontal acceleration from inputs
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		moveInput -= 1;
		//playerVel.x = -GameConstants::PLAYER_MAX_MOVE_SPEED;
		playerVel.x -= GameConstants::PLAYER_MOVE_ACCELERATION * delta;
		playerVel.x = std::max(playerVel.x, -GameConstants::PLAYER_MAX_MOVE_SPEED);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		moveInput += 1;
		//playerVel.x = GameConstants::PLAYER_MAX_MOVE_SPEED;
		playerVel.x += GameConstants::PLAYER_MOVE_ACCELERATION * delta;
		playerVel.x = std::min(playerVel.x, GameConstants::PLAYER_MAX_MOVE_SPEED);
	}

	if (moveInput == 0 || sign(playerVel.x) != sign(moveInput))
	{
		playerVel.x *= std::powf(GameConstants::PLAYER_DECELARATION_MULTIPLIER, delta);
	}

	// Handle jumping
	if (isGrounded())
	{
		if (playerVel.y > 0) mIsGrounded = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			playerVel.y = GameConstants::PLAYER_JUMP_SPEED;
			mIsGrounded = false;
			mIsJumping = true;
		}
	}

	// Jump higher if key is held
	if (mIsJumping)
	{
		mIsJumping = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
	}
	else
	{
		playerVel.y = std::max(playerVel.y, GameConstants::PLAYER_MIN_JUMP_SPEED);
	}

	setVelocity(playerVel);
}
