#include "Sprite.h"
#include <SimpleMath.h>
#include "TextureCache.h"

using namespace DirectX::SimpleMath;


Sprite::Sprite()
	: mPos(0, 0), mScale(1, 1), mRotation(0), mOrigin(0, 0), mColor(Colors::White.v), mpTexture(nullptr), mpTextureRect(nullptr)
{
	RECT test = { 0,0,500,500 };
	mpTextureRect = &test;
}

Sprite::Sprite(ID3D11ShaderResourceView& texture)
	: Sprite()
{
	setTexture(texture);
}

Sprite::Sprite(ID3D11ShaderResourceView& texture, RECT rect)
	: Sprite(texture)
{
	setTextureRect(rect);
}

Sprite::~Sprite()
{
}

void Sprite::render(DirectX::SpriteBatch& batch)
{
	batch.Draw(mpTexture, mPos, mTextureRect ? &mTextureRect.value() : nullptr, mColor, mRotation, mOrigin, mScale, DirectX::SpriteEffects::SpriteEffects_None);
}

void Sprite::setTexture(ID3D11ShaderResourceView& texture)
{
	mpTexture = &texture;
}

void Sprite::setTexture(ID3D11ShaderResourceView& texture, RECT rect)
{
	setTexture(texture);
	setTextureRect(rect);
}

ID3D11ShaderResourceView& Sprite::getTexture() const
{
	return *mpTexture;
}

void Sprite::setTextureRect(RECT rect)
{
	mpTextureRect = &rect;
}

RECT Sprite::getTextureRect() const
{
	return *mpTextureRect;
}
