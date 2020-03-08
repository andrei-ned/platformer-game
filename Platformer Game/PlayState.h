#pragma once
#include "State.h"
#include "GameObject.h"
#include "PhysicsBody.h"
#include "Sprite.h"
#include "Text.h"

class PlayState : public State
{
public:
	PlayState(StateMachine& stateMachine);
	~PlayState();
	void update(const float deltaTime) override;
	void render(Camera& camera) override;
private:
	std::vector<GameObject*> mAllGameObjects;
	std::vector<PhysicsBody*> mAllPhysicsBodies;
	std::vector<Collider*> mAllColliders;
	std::vector<Sprite*> mBackgroundSprites;
	GameObject* mpPlayer;
	// **DEBUG
	Text* mpDebugText;
};

