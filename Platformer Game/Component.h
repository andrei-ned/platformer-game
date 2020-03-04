#pragma once
#include "SpriteBatch.h"

class GameObject;

// Base Component class that all other components inherit from
class Component
{
public:
	// Will be called every frame, used for game logic
	virtual void update(const float deltaTime) {}
	// Will be called every frame, separate from update to order certain logic (e.g. input in update, then resolve all collisions, then physics logic in updateLate)
	virtual void updateLate(const float deltaTime) {}
	// Will be called by game every frame, used for rendering
	virtual void render(DirectX::SpriteBatch& batch) {}
protected:
	GameObject* mpGameObject;
	Component(GameObject& gameObject);
};

