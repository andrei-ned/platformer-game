#pragma once
#include <cstring>

// Container for game related constants, tweak as necessary
namespace GameConstants {
	// Desired resolution width
	const int SCREEN_RES_X = 1280;
	// Desired resolution height
	const int SCREEN_RES_Y = 896;
	const std::string WINDOW_NAME = "Game";
	// Gravity to be applied to player, in pixels per second
	const float GRAVITY = 700.0f;
	// Movement speed of player, in pixels per second
	const float PLAYER_SPEED = 20.0f;
}
