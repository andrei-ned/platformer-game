#pragma once
#include "SimpleMath.h"
#include "Helpers.h"

struct Level
{
	Level(RECTF b, DirectX::SimpleMath::Vector2 pos) : bounds(b), playerSpawnPos(pos) {}
	RECTF bounds;
	DirectX::SimpleMath::Vector2 playerSpawnPos;
};

