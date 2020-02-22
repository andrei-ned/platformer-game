#include "Sprite.h"



Sprite::Sprite()
	: mPos(0, 0), mScale(1, 1), mRotation(0), mOrigin(0, 0), mColor(Colors::White.v), mpTexture(nullptr), mpTextureRect(nullptr)
{
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
	batch.Draw(mpTexture, mPos, mpTextureRect, mColor, mRotation, mOrigin, mScale, DirectX::SpriteEffects::SpriteEffects_None);
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
