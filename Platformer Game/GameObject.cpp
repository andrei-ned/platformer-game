#include "GameObject.h"
#include <cassert>
#include <algorithm>
#include "Helpers.h"
#include "GameConstants.h"

GameObject::GameObject() : mPos(0, 0), mScale(1, 1), mRotation(0), mOrigin(0, 0), mColor(Colors::White.v) {}

GameObject::~GameObject()
{
	for (auto& pair : mComponents)
	{
		delete pair.second;
	}
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

void GameObject::render(DirectX::SpriteBatch& batch)
{
	for (auto& pair : mComponents)
	{
		pair.second->render(batch);
	}
}
