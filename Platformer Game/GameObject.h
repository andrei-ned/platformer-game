#pragma once
//#include <SFML/Graphics.hpp>
#include <iostream>

// Base game object class that all other game objects inherit from
class GameObject
{
public:
	// Will be called by game every frame, used for rendering
	//void render(sf::RenderWindow& window);
	//void setOrigin(const sf::Vector2f& off);
	//sf::Vector2f getOrigin() const;
	//void setScale(const sf::Vector2f& s);
	//sf::Vector2f getScale() const;
	//void setPos(const sf::Vector2f& pos);
	//sf::Vector2f getPos() const;
	//float getDegrees() const;
	//void setDegrees(float angle);
	//void addRotation(float angle);
protected:
	GameObject();
	//// Pointer to drawable, must be initialized by inheriting game object
	//sf::Drawable* mDrawable;
	//// Pointer to transformable, must be initialized by inheriting game object
	//sf::Transformable* mTransformable;
};

