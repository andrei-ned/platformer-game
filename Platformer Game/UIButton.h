#pragma once
#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include <functional>
#include "Event.h"

class GameObject;

class UIButton : public Component
{
public:
	Event<> mOnClick;
	Color mColorDefault;
	Color mColorHovered;
	Color mColorPressed;

	UIButton(GameObject& gameObject);
	~UIButton() override;

	void start() override;
	void update(const float deltaTime) override;
private:
	Sprite* mpSprite;
	Collider* mpCollider;

	enum class ButtonState { Default, Hovered, Pressed } mState;
};

