#include "UIButton.h"
#include "GameObject.h"
#include "Mouse.h"

UIButton::UIButton(GameObject& gameObject) : Component(gameObject), mColorDefault(Colors::White.v), mColorHovered(.9f, .9f, .9f, 1), mColorPressed(.8f, .8f, .8f, 1), mState(ButtonState::Default)
{
}


UIButton::~UIButton()
{
}


void UIButton::start()
{
	mpSprite = mpGameObject->getComponent<Sprite>();
	mpCollider = mpGameObject->getComponent<Collider>();
}

void UIButton::update(const float deltaTime)
{
	auto mouseState = Mouse::Get().GetState();

	if (mpCollider->containsPoint(Vector2(static_cast<float>(mouseState.x), static_cast<float>(mouseState.y)))) // Cursor is on button
	{
		if (mouseState.leftButton) // Left click is pressed
		{
			mState = ButtonState::Pressed;
			mpSprite->mColor = mColorPressed;
		}
		else
		{
			if (mState == ButtonState::Pressed) // Trigger onClick when LMB is unpressed
			{
				//mOnClick();
				mOnClick.invoke();
			}
			mState = ButtonState::Hovered;
			mpSprite->mColor = mColorHovered;
		}
	}
	else
	{
		mState = ButtonState::Default;
		mpSprite->mColor = mColorDefault;
	}
}
