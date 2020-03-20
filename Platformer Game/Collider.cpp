#include "Collider.h"
#include "GameObject.h"
#include "Sprite.h"

Collider::Collider(GameObject& gameObject) : Component(gameObject), mOrigin(0, 0), mSize(0, 0)
{
}


Collider::~Collider()
{
}

void Collider::start()
{
	if (mSize.x > 0 || mSize.y > 0)
		return;
	// Get size from sprite
	auto spr = mpGameObject->getComponent<Sprite>();
	if (spr)
	{
		RECT rect = spr->getTextureRect();
		mSize.x = static_cast<float>(rect.right - rect.left) * spr->mScale.x;
		mSize.y = static_cast<float>(rect.bottom - rect.top) * spr->mScale.y;
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

void Collider::setBounds(RECTF rect)
{
	auto spr = mpGameObject->getComponent<Sprite>();
	assert(spr);
	mSize.x = rect.right - rect.left;
	mSize.y = rect.bottom - rect.top;
	mSize *= spr->mScale;
	mOrigin = spr->mOrigin;
	RECT sprRect = spr->getTextureRect();
	mOrigin.x += (sprRect.left - rect.left) * spr->mScale.x;
	mOrigin.y += (sprRect.top - rect.top) * spr->mScale.y;
}

bool Collider::containsPoint(Vector2 point) const
{
	RECTF bounds = getBounds();
	return point.x > bounds.left && point.x < bounds.right && point.y > bounds.top && point.y < bounds.bottom;
}
