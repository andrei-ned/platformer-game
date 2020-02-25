#pragma once
//#include <SFML/Graphics.hpp>
#include <iostream>
#include "SpriteBatch.h"
#include "SimpleMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// Base game object class that all other game objects inherit from
class GameObject
{
public:
	// Will be called by game every frame, used for rendering
	//void render(SpriteBatch& spriteBatch);
	//void setOrigin(const Vector2 off);
	//Vector2 getOrigin() const;
	//void setScale(const Vector2 s);
	//Vector2 getScale() const;
	//void setPos(const Vector2 pos);
	//Vector2 getPos() const;
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

