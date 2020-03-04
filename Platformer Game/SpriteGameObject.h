#pragma once
#include "GameObject.h"
#include "SpriteBatch.h"
#include "SimpleMath.h"
#include "Helpers.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// Game object that uses a sprite
class SpriteGameObject : public GameObject
{
public:
	SpriteGameObject();
	SpriteGameObject(ID3D11ShaderResourceView& texture);
	SpriteGameObject(ID3D11ShaderResourceView& texture, RECT rect);
	~SpriteGameObject();
	void render(DirectX::SpriteBatch& batch);
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

