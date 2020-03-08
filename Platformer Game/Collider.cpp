#include "Collider.h"
#include "GameObject.h"
#include "Sprite.h"

Collider::Collider(GameObject& gameObject) : Component(gameObject), mOrigin(0, 0)
{
}


Collider::~Collider()
{
}

void Collider::start()
{
	auto spr = mpGameObject->getComponent<Sprite>();
	if (spr)
	{
		RECT rect = spr->getTextureRect();
		mSize.x = static_cast<float>(rect.right - rect.left);
		mSize.y = static_cast<float>(rect.bottom - rect.top);
		mOrigin = spr->mOrigin;
	}
}

RECTF Collider::getBounds() const
{
	float minX = mpGameObject->mPos.x - mOrigin.x;
	float minY = mpGameObject->mPos.y - mOrigin.y;
	float maxX = mpGameObject->mPos.x - mOrigin.x + mpGameObject->mScale.x * mSize.x;
	float maxY = mpGameObject->mPos.y - mOrigin.y + mpGameObject->mScale.y * mSize.y;
	return { minX, minY, maxX, maxY };
}
