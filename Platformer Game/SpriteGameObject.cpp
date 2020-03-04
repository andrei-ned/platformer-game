#include "SpriteGameObject.h"
#include "D3DHelpers.h"

SpriteGameObject::SpriteGameObject() : mpTexture(nullptr)
{
}

SpriteGameObject::SpriteGameObject(ID3D11ShaderResourceView& texture)
	: mpTexture(&texture), mTextureRect(getMaxTextureRect(&texture))
{
}

SpriteGameObject::SpriteGameObject(ID3D11ShaderResourceView& texture, RECT rect)
	: mpTexture(&texture), mTextureRect(rect)
{
}

SpriteGameObject::~SpriteGameObject()
{
}

void SpriteGameObject::render(DirectX::SpriteBatch& batch)
{
	assert(mpTexture);
	batch.Draw(mpTexture, mPos, &mTextureRect, mColor, mRotation, mOrigin, mScale, DirectX::SpriteEffects::SpriteEffects_None);
}

void SpriteGameObject::setTexture(ID3D11ShaderResourceView& texture)
{
	mpTexture = &texture;
	setTextureRect(getMaxTextureRect(&texture));
}

void SpriteGameObject::setTexture(ID3D11ShaderResourceView& texture, RECT rect)
{
	mpTexture = &texture;
	setTextureRect(rect);
}

ID3D11ShaderResourceView& SpriteGameObject::getTexture() const
{
	return *mpTexture;
}

void SpriteGameObject::setTextureRect(RECT rect)
{
	mTextureRect = rect;
}

RECT SpriteGameObject::getTextureRect() const
{
	return mTextureRect;
}

RECTF SpriteGameObject::getBounds() const
{
	float minX = mPos.x + mOrigin.x;
	float minY = mPos.y + mOrigin.y;
	float maxX = mPos.x + mOrigin.x + mScale.x * (mTextureRect.right - mTextureRect.left);
	float maxY = mPos.y + mOrigin.y + mScale.y * (mTextureRect.bottom - mTextureRect.top);
	return { minX, minY, maxX, maxY };
}
