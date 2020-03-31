#include "GameObjectUtils.h"
#include "TextureCache.h"
#include "Sprite.h"
#include "Text.h"
#include "FontCache.h"
#include "Collider.h"
#include "UIButton.h"
#include <memory>

std::unique_ptr<GameObject> makeUIButton(std::string buttonText)
{
	auto button = std::make_unique<GameObject>();
	button->mIsInWorldSpace = false;
	auto spr = button->addComponent<Sprite>();
	spr->setTexture(*TextureCache::get().LoadTexture("UI/buttons.png", false), { 488, 50, 488 + 512, 50 + 128 });
	spr->mOrigin = Vector2(256, 64);
	spr->mScale = Vector2(0.75f, 0.75f);
	auto txt = button->addComponent<Text>();
	txt->setFont(*FontCache::get().LoadSpriteFont("courier.spritefont"));
	txt->mString = buttonText;
	txt->mOrigin = txt->getDimensions() / 2;
	button->addComponent<Collider>();
	button->addComponent<UIButton>();
	return button;
}
