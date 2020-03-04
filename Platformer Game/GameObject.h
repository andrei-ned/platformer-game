#pragma once
#include <iostream>
#include "SpriteBatch.h"
#include "SimpleMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// Base game object class that all other game objects inherit from
class GameObject
{
public:
	Vector2 mPos;
	Vector2 mScale;
	float mRotation; // in radians
	Vector2 mOrigin;
	Color mColor;
	// Will be called by game every frame, used for rendering
	virtual void render(DirectX::SpriteBatch& batch) = 0;
protected:
	GameObject();
};

