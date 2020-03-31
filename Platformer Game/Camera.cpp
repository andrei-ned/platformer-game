#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera(SpriteBatch& spriteBatch, D3D11_VIEWPORT& viewport) : mpSpriteBatch(&spriteBatch), mpViewport(&viewport)
{
}


Camera::~Camera()
{
}

void Camera::drawSprite(ID3D11ShaderResourceView* texture, const Vector2& pos, const RECT* textureRect, Color color, float rotation, const Vector2& origin,
	const Vector2& scale, bool isWorldPos, SpriteEffects spriteEffects, float depth)
{
	mpSpriteBatch->Draw(texture, isWorldPos ? pos - mPos : pos, textureRect, color, rotation, origin, scale, spriteEffects, depth);
}

void Camera::drawText(SpriteFont* font, const std::string text, const Vector2& pos, Color color, float rotation, const Vector2& origin,
	const Vector2& scale, bool isWorldPos, SpriteEffects spriteEffects, float depth)
{
	font->DrawString(mpSpriteBatch, text.c_str(), isWorldPos ? pos - mPos : pos, color, rotation, origin, scale, spriteEffects, depth);
}

void Camera::centerOn(Vector2 targetPos)
{
	mPos = Vector2(targetPos.x - mpViewport->Width / 2, targetPos.y - mpViewport->Height / 2);
}

Vector2 Camera::getCenter() const
{
	return Vector2(mPos.x + mpViewport->Width / 2, mPos.y + mpViewport->Height / 2);
}

Vector2 Camera::getDimensions() const
{
	return Vector2(mpViewport->Width, mpViewport->Height);
}
