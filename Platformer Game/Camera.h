#pragma once
#include "D3DHelpers.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"


// Handles rendering, to be passed in render functions (additional abstraction instead of just passing the sprite batch), also has a position and can be moved
class Camera
{
public:
	DirectX::SimpleMath::Vector2 mPos; // The top left corner of the camera

	Camera(DirectX::SpriteBatch& spriteBatch, D3D11_VIEWPORT& viewport);
	~Camera();

	void drawSprite(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& pos, const RECT* textureRect, DirectX::SimpleMath::Color color, float rotation, const DirectX::SimpleMath::Vector2& origin,
		const DirectX::SimpleMath::Vector2& scale, bool isWorldPos = true, DirectX::SpriteEffects spriteEffects = DirectX::SpriteEffects_None, float depth = 0.0f);
	void drawText(DirectX::SpriteFont* font, const std::string text, const DirectX::SimpleMath::Vector2& pos, DirectX::SimpleMath::Color color, float rotation, const DirectX::SimpleMath::Vector2& origin,
		const DirectX::SimpleMath::Vector2& scale, bool isWorldPos = true, DirectX::SpriteEffects spriteEffects = DirectX::SpriteEffects_None, float depth = 0.0f);

	// Center the camera on a position
	void centerOn(DirectX::SimpleMath::Vector2 targetPos);

	DirectX::SimpleMath::Vector2 getCenter() const;
	DirectX::SimpleMath::Vector2 getDimensions() const;
private:
	DirectX::SpriteBatch* mpSpriteBatch;
	D3D11_VIEWPORT* mpViewport;
};

