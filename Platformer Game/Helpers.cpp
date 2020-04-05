#include "Helpers.h"

using namespace DirectX::SimpleMath;

float sign(float x)
{
	return x > 0 ? 1.0f : -1.0f;
}

DirectX::SimpleMath::Vector2 rotate(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector2 origin, float angle)
{
	if (angle != 0)
	{
		float s = sin(angle);
		float c = cos(angle);

		// Translate to origin
		pos -= origin;

		Vector2 oldPos = pos;
		// Rotate
		pos.x = oldPos.x * c - oldPos.y * s;
		pos.y = oldPos.x * s + oldPos.y * c;

		// Translate back
		pos += origin;
	}

	return pos;
}

bool RECTF::containsPoint(const Vector2 point) const
{
	return point.x > left && point.x < right && point.y > top && point.y < bottom;
}
