#include "Player.h"
#include "GameConstants.h"


Player::Player() {
}


Player::~Player() {
}

void Player::updateInput(const sf::Time& deltaTime) {
	// **NO GRAVITY FOR TESTING
	sf::Vector2f playerVel(0, 0);//GameConstants::GRAVITY);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		playerVel.x -= GameConstants::PLAYER_MAX_SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		playerVel.x += GameConstants::PLAYER_MAX_SPEED;
	}

	// **FOR TESTING ONLY
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		playerVel.y -= GameConstants::PLAYER_MAX_SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		playerVel.y += GameConstants::PLAYER_MAX_SPEED;
	}

	setVelocity(playerVel);
}
