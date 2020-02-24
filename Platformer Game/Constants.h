#pragma once
//#include "SFML/Graphics.hpp"
#include <cstring>

// Container for constants, these need not be changed
namespace Constants {
	const char ESCAPE_KEY{ 27 };         // ASCII code for Escape key
	const char ENTER_KEY{ 13 };          // ASCII code for Enter key
	//const sf::Uint32 ASCII_RANGE{ 127 }; // Relevant ASCII Range
	// File paths
	const std::string ASSETS_PATH = "../Assets/";
	const std::string TEXTURES_PATH = "../Assets/Textures/";
}
