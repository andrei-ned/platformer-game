#include "Collider.h"
#include "GameObject.h"
#include "Sprite.h"

using namespace DirectX::SimpleMath;


Collider::Collider(GameObject& gameObject) : Component(gameObject), mOrigin(0, 0), mSize(0, 0), mIsTrigger(false)
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
	Vector2 rotationOrigin = mpGameObject->mPos - mOrigin;

	Vector2 p1 = rotate(mpGameObject->mPos - mOrigin, rotationOrigin, mpGameObject->mRotation);
	Vector2 p2 = rotate(mpGameObject->mPos - mOrigin + Vector2(mpGameObject->mScale.x * mSize.x, 0), rotationOrigin, mpGameObject->mRotation);
	Vector2 p3 = rotate(mpGameObject->mPos - mOrigin + Vector2(0, mpGameObject->mScale.y * mSize.y), rotationOrigin, mpGameObject->mRotation);
	Vector2 p4 = rotate(mpGameObject->mPos - mOrigin + Vector2(mpGameObject->mScale.x * mSize.x, mpGameObject->mScale.y * mSize.y), rotationOrigin, mpGameObject->mRotation);

	float minX = min(min(p1.x, p2.x), min(p3.x, p4.x));
	float minY = min(min(p1.y, p2.y), min(p3.y, p4.y));
	float maxX = max(max(p1.x, p2.x), max(p3.x, p4.x));
	float maxY = max(max(p1.y, p2.y), max(p3.y, p4.y));

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

bool Collider::containsPoint(const Vector2 point) const
{
	RECTF bounds = getBounds();
	return bounds.containsPoint(point);
}
