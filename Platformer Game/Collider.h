#pragma once
#include "Component.h"
#include "SimpleMath.h"
#include "Helpers.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Collider : public Component
{
public:
	Vector2 mOrigin;
	Vector2 mSize;
	Collider(GameObject& gameObject);
	~Collider();
	void start() override;
	// Returns bounds (i.e. position and size in world space)
	RECTF getBounds() const;
	// Sets size and origin based on texture rect
	void setBounds(RECTF rect);
	// Returns true if position is inside of collider
	bool containsPoint(Vector2 point) const;
};

