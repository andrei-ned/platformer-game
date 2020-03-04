#pragma once
#include "Component.h"
#include "SimpleMath.h"
#include "Helpers.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Sprite : public Component
{
public:
	Vector2 mOrigin;
	Color mColor;
	Sprite(GameObject& gameObject);
	~Sprite();
	void render(DirectX::SpriteBatch& batch) override;
	void setTexture(ID3D11ShaderResourceView& texture);
	void setTexture(ID3D11ShaderResourceView& texture, RECT rect);
	ID3D11ShaderResourceView& getTexture() const;
	void setTextureRect(RECT rect);
	RECT getTextureRect() const;
	// Returns bounds (i.e. position and size in world space)
	RECTF getBounds() const;
private:
	ID3D11ShaderResourceView *mpTexture;
	RECT mTextureRect;
};

