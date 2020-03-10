#include "Sprite.h"
#include "GameObject.h"
#include "D3DHelpers.h"


Sprite::Sprite(GameObject& gameObject) : Component(gameObject), mOrigin(0, 0), mScale(1, 1), mColor(Colors::White.v)
{
}


Sprite::~Sprite()
{
}


void Sprite::render(Camera& camera)
{
	assert(mpTexture);
	camera.drawSprite(mpTexture, mpGameObject->mPos, &mTextureRect, mColor, mpGameObject->mRotation, mOrigin, mpGameObject->mScale * mScale, mpGameObject->mIsInWorldSpace, SpriteEffects_None);
}

void Sprite::setTexture(ID3D11ShaderResourceView& texture)
{
	mpTexture = &texture;
	mTextureRect = getMaxTextureRect(&texture);
}

void Sprite::setTexture(ID3D11ShaderResourceView& texture, RECT rect)
{
	mpTexture = &texture;
	mTextureRect = rect;
}

ID3D11ShaderResourceView& Sprite::getTexture() const
{
	return *mpTexture;
}

void Sprite::setTextureRect(RECT rect)
{
	mTextureRect = rect;
}

RECT Sprite::getTextureRect() const
{
	return mTextureRect;
}

RECTF Sprite::getBounds() const
{
	float minX = mpGameObject->mPos.x - mOrigin.x;
	float minY = mpGameObject->mPos.y - mOrigin.y;
	float maxX = mpGameObject->mPos.x - mOrigin.x + mpGameObject->mScale.x * (mTextureRect.right - mTextureRect.left);
	float maxY = mpGameObject->mPos.y - mOrigin.y + mpGameObject->mScale.y * (mTextureRect.bottom - mTextureRect.top);
	return { minX, minY, maxX, maxY };
}
