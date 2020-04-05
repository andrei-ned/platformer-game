#pragma once
#include <d3d11.h>
#include "SimpleMath.h"


// Returns sign of x
float sign(float x);

// Returns rotated position around an origin (in radians)
DirectX::SimpleMath::Vector2 rotate(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector2 origin, float angle);

// Rectangle identifier with float instead of int
struct RECTF
{
	float left, top, right, bottom;
	bool containsPoint(const DirectX::SimpleMath::Vector2 point) const;
};
