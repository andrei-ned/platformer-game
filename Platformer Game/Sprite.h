#pragma once
#include "Component.h"
#include "SimpleMath.h"
#include "Helpers.h"


class Sprite : public Component
{
public:
	DirectX::SimpleMath::Vector2 mOrigin;
	DirectX::SimpleMath::Vector2 mScale;
	DirectX::SimpleMath::Color mColor;
	DirectX::SpriteEffects mSpriteEffects;

	Sprite(GameObject& gameObject);
	~Sprite() override;

	virtual void render(Camera& camera) override;
	void setTexture(ID3D11ShaderResourceView& texture);
	void setTexture(ID3D11ShaderResourceView& texture, RECT rect);
	ID3D11ShaderResourceView& getTexture() const;
	void setTextureRect(RECT rect);
	RECT getTextureRect() const;
	// Returns bounds (i.e. position and size in world space)
	RECTF getBounds() const;
	RECT mTextureRect;
private:
	ID3D11ShaderResourceView *mpTexture;
};

