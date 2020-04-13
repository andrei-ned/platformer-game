#pragma once
#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include <functional>
#include "Event.h"

class GameObject;


// Handles mouse input on an UI element, triggering an event and changing color on hover/click
class UIButton : public Component
{
public:
	Event<> mOnClick;
	DirectX::SimpleMath::Color mColorDefault;
	DirectX::SimpleMath::Color mColorHovered;
	DirectX::SimpleMath::Color mColorPressed;

	UIButton(GameObject& gameObject);
	~UIButton() override;

	void start() override;
	void update(const float deltaTime) override;
private:
	Sprite* mpSprite;
	Collider* mpCollider;

	enum class ButtonState { Default, Hovered, Pressed } mState;
};

