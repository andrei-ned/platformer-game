#pragma once
#include <cstring>

// Container for game related constants, tweak as necessary
namespace GameConstants {
	// Desired resolution width
	const int SCREEN_RES_X = 1280;
	// Desired resolution height
	const int SCREEN_RES_Y = 896;
	const std::string WINDOW_NAME = "Game";
	// Gravity to be applied to player
	const float GRAVITY = 10000.0f;
	// Max fall speed
	const float MAX_FALL_SPEED = 10000.0f;
	// Acceleration to be applied to player on movement input
	const float PLAYER_MOVE_ACCELERATION = 6000.0f;
	// Max horizontal move velocity
	const float PLAYER_MAX_MOVE_SPEED = 1000.0f;
	// Horizontal velocity is multiplied by this per second
	const float PLAYER_DECELARATION_MULTIPLIER = .00001f;
	// Vertical velocity is set to this on jump input
	const float PLAYER_JUMP_SPEED = -2500.0f;
	// Vertical velocity is set to this when letting go of jump input (holding the jump button means a higher jump)
	const float PLAYER_MIN_JUMP_SPEED = -1000.0f;
}
