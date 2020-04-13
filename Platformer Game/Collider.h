#pragma once
#include "Component.h"
#include "SimpleMath.h"
#include "Helpers.h"
#include "Event.h"

// To give an object a box of a certain size (to be used for collisions etc)
class Collider : public Component
{
public:
	DirectX::SimpleMath::Vector2 mOrigin;
	DirectX::SimpleMath::Vector2 mSize;
	bool mIsTrigger;
	Event<Collider&> mOnTrigger;

	Collider(GameObject& gameObject);
	~Collider() override;

	void start() override;
	// Returns bounds (i.e. position and size in world space)
	RECTF getBounds() const;
	// Sets size and origin based on texture rect
	void setBounds(RECTF rect);
	// Returns true if position is inside of collider
	bool containsPoint(const DirectX::SimpleMath::Vector2 point) const;
};

