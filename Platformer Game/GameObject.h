#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

// Base game object class that all other game objects inherit from
class GameObject
{
public:
	// Will be called by game every frame, used for rendering
	void render(sf::RenderWindow& window);
	void setOrigin(const sf::Vector2f& off);
	sf::Vector2f getOrigin() const;
	void setScale(const sf::Vector2f& s);
	sf::Vector2f getScale() const;
	void setPos(const sf::Vector2f& pos);
	sf::Vector2f getPos() const;
	float getDegrees() const;
	void setDegrees(float angle);
	void addRotation(float angle);
protected:
	GameObject();
	// Pointer to drawable, must be initialized by inheriting game object
	sf::Drawable* mDrawable;
	// Pointer to transformable, must be initialized by inheriting game object
	sf::Transformable* mTransformable;
};

// Game object that uses a sprite
class SpriteGameObject : public GameObject
{
public:
	SpriteGameObject();
	SpriteGameObject(const sf::Texture& t);
	SpriteGameObject(const sf::Texture& t, const sf::IntRect& rect);
	void setTexture(const sf::Texture& t);
	void setTexture(const sf::Texture& t, const sf::IntRect& rect);
protected:
	sf::Sprite mSprite;
};

// Implements physics on top of SpriteGameObject
class PhysicsGameObject : public SpriteGameObject
{
public:
	PhysicsGameObject();
	// Should be called every frame to apply velocity
	void update(const sf::Time& deltaTime);
	sf::Vector2f getVelocity() const;
	void setVelocity(const sf::Vector2f& v);
	// Returns true if the 2 objects intersect
	bool checkForCollision(const PhysicsGameObject& other) const;
	// Returns size in world space
	sf::Vector2f getDimensions() const;
private:
	sf::Vector2f mVelocity;
};

// Game object that uses text
class TextGameObject : public GameObject
{
public:
	TextGameObject();
	void setFont(sf::Font& font);
	void setCharacterPixelSize(int size);
	int getCharacterPixelSize() const;
	void setString(std::string s);
	std::string getString() const;
private:
	sf::Text mText;
};

