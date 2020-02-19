#pragma once
#include "GameObject.h"

// Game object that uses a sprite
class SpriteGameObject : public GameObject
{
public:
	SpriteGameObject();
	//SpriteGameObject(const sf::Texture& t);
	//SpriteGameObject(const sf::Texture& t, const sf::IntRect& rect);
	//void setTexture(const sf::Texture& t);
	//void setTexture(const sf::Texture& t, const sf::IntRect& rect);
	//// Returns size in world space
	//sf::Vector2f getDimensions() const;
	//// Returns bounds (i.e. position and size in world space)
	//sf::FloatRect getBounds() const;
	// Returns true if the 2 objects intersect
	bool intersects(const SpriteGameObject& other) const;
protected:
	//sf::Sprite mSprite;
};

