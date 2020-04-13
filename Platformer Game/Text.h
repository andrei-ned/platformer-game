#pragma once
#include "Component.h"
#include "SimpleMath.h"
#include "SpriteFont.h"


// Renders text
class Text : public Component
{
public:
	DirectX::SimpleMath::Vector2 mOrigin;
	DirectX::SimpleMath::Vector2 mScale;
	DirectX::SimpleMath::Color mColor;
	DirectX::SpriteEffects mSpriteEffects;
	std::string mString;

	Text(GameObject& gameObject);
	~Text() override;

	virtual void render(Camera& camera) override;
	void setFont(DirectX::SpriteFont& font);
	// Get size based on font and string
	DirectX::SimpleMath::Vector2 getDimensions() const;
private:
	DirectX::SpriteFont *mpFont;
};

