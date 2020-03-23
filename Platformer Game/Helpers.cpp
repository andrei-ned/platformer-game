#include "Helpers.h"

float sign(float x)
{
	return x > 0 ? 1.0f : -1.0f;
}

bool RECTF::containsPoint(const Vector2 point) const
{
	return point.x > left && point.x < right && point.y > top && point.y < bottom;
}
