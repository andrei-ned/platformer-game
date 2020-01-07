#pragma once
#include "GameObject.h"

class Player : public PhysicsGameObject
{
public:
	/// <summary> Update player velocity based on input, to be called every frame before PhysicsGameObject's update</summary>
	/// <param name="deltaTime"> Time since last frame </param>
	void updateInput(const sf::Time& deltaTime);
	Player();
	~Player();
};

