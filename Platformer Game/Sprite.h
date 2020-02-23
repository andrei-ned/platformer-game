#pragma once
#include "SpriteBatch.h"
#include "SimpleMath.h"
#include <optional>

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Sprite
{
public:
	Vector2 mPos;
	Vector2 mScale;
	float mRotation; // in radians
	Vector2 mOrigin;
	Color mColor;

	Sprite();
	Sprite(ID3D11ShaderResourceView& texture);
	Sprite(ID3D11ShaderResourceView& texture, RECT rect);
	~Sprite();
	void render(DirectX::SpriteBatch& batch);
	void setTexture(ID3D11ShaderResourceView& texture);
	void setTexture(ID3D11ShaderResourceView& texture, RECT rect);
	ID3D11ShaderResourceView& getTexture() const;
	void setTextureRect(RECT rect);
	RECT getTextureRect() const;
	// Returns size in world space
	//sf::Vector2f getDimensions() const;
	// Returns bounds (i.e. position and size in world space)
private:
	ID3D11ShaderResourceView *mpTexture;
	std::optional<RECT> mTextureRect;
	RECT *mpTextureRect;
};

