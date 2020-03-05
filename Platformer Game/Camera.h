#pragma once
#include "D3DHelpers.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Camera
{
public:
	Vector2 mPos;
	Camera(SpriteBatch& spriteBatch);
	~Camera();
	void drawSprite(ID3D11ShaderResourceView* texture, const Vector2& pos, const RECT* textureRect, Color color, float rotation, const Vector2& origin, const Vector2& scale, bool isWorldPos = true);
	void drawText(SpriteFont* font, const std::string text, const Vector2& pos, Color color, float rotation, const Vector2& origin, const Vector2& scale, bool isWorldPos = true);
private:
	SpriteBatch* mpSpriteBatch;
};

