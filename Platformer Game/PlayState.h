#pragma once
#include "State.h"
#include "GameObject.h"
#include "PhysicsBody.h"
#include "Sprite.h"
#include "Text.h"
#include <memory>
#include "Level.h"


// State containing the player and the levels
class PlayState : public State
{
public:
	PlayState(StateMachine& stateMachine);
	~PlayState() override;
	void update(const float deltaTime) override;
	void render(Camera& camera) override;
private:
	void addGameObjects(std::vector<GameObject*> newGameObjects);

	std::vector<std::unique_ptr<GameObject>> mAllGameObjects;
	std::vector<PhysicsBody*> mAllPhysicsBodies;
	std::vector<Collider*> mAllColliders;
	std::vector<Sprite*> mBackgroundSprites;
	GameObject* mpPlayer;
	// Levels
	std::vector<Level> mLevels;
	int mCurrentLevelIndex;
	// **DEBUG
	//Text* mpDebugText;
};

