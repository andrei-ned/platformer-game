#pragma once
#include <d3d11.h>
#include "SimpleMath.h"


// Returns sign of x
float sign(float x);

// Rectangle identifier with float instead of int
struct RECTF
{
	float left, top, right, bottom;
	bool containsPoint(const  DirectX::SimpleMath::Vector2 point) const;
};
