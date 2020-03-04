#pragma once
#include "Component.h"
#include "SimpleMath.h"
#include "SpriteFont.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Text : public Component
{
public:
	Vector2 mOrigin;
	Color mColor;
	std::string mString;
	Text(GameObject& gameObject);
	~Text();
	void render(DirectX::SpriteBatch& batch) override;
	void setFont(SpriteFont& font);
private:
	SpriteFont *mpFont;
};

