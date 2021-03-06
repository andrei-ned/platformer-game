#include "GameObject.h"
#include <cassert>
#include <algorithm>
#include "Helpers.h"
#include "GameConstants.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

GameObject::GameObject() : mPos(0, 0), mScale(1, 1), mRotation(0), mIsInWorldSpace(true) {}

GameObject::~GameObject()
{
	mComponents.clear();
}

void GameObject::start()
{
	for (auto& pair : mComponents)
	{
		pair.second->start();
	}
}

void GameObject::update(const float deltaTime)
{
	for (auto& pair : mComponents)
	{
		pair.second->update(deltaTime);
	}
}

void GameObject::updateLate(const float deltaTime)
{
	for (auto& pair : mComponents)
	{
		pair.second->updateLate(deltaTime);
	}
}

void GameObject::render(Camera& camera)
{
	for (auto& pair : mComponents)
	{
		pair.second->render(camera);
	}
}
