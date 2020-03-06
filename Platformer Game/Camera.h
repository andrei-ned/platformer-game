#pragma once
#include "D3DHelpers.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Camera
{
public:
	Vector2 mPos; // The top left corner of the camera
	Camera(SpriteBatch& spriteBatch, D3D11_VIEWPORT& viewport);
	~Camera();
	void drawSprite(ID3D11ShaderResourceView* texture, const Vector2& pos, const RECT* textureRect, Color color, float rotation, const Vector2& origin, const Vector2& scale, bool isWorldPos = true);
	void drawText(SpriteFont* font, const std::string text, const Vector2& pos, Color color, float rotation, const Vector2& origin, const Vector2& scale, bool isWorldPos = true);
	// Center the camera on a position
	void centerOn(Vector2 targetPos);
private:
	SpriteBatch* mpSpriteBatch;
	D3D11_VIEWPORT* mpViewport;
};

