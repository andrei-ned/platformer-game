#pragma once
#include <d3d11.h>
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

// Returns sign of x
float sign(float x);

// Rectangle identifier with float instead of int
struct RECTF
{
	float left, top, right, bottom;
	bool containsPoint(const Vector2 point) const;
};
