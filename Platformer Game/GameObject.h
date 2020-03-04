#pragma once
#include <iostream>
#include "SpriteBatch.h"
#include "SimpleMath.h"
#include <unordered_map>
#include "Component.h"
#include <typeindex>

using namespace DirectX;
using namespace DirectX::SimpleMath;

// Game object class, add components to give functionality
class GameObject
{
public:
	GameObject();
	~GameObject();
	Vector2 mPos;
	Vector2 mScale;
	float mRotation; // in radians
	Vector2 mOrigin; // <- remove
	Color mColor; // <- remove
	// Will be called every frame, used for game logic
	void update(const float deltaTime);
	// Will be called every frame, separate from update to order certain logic (e.g. input in update, then resolve all collisions, then physics logic in updateLate)
	void updateLate(const float deltaTime);
	// Will be called by game every frame, used for rendering
	void render(DirectX::SpriteBatch& batch);
	//template <class T>
	//T* addComponent()
	//{
	//	auto pT = new T(*this);
	//	mComponents.insert({ typeid(T), pT });
	//	return pT;
	//}

	//template <class T>
	//void removeComponent()
	//{
	//	auto search = mComponents.find(typeid(T));
	//	if (search != mComponents.end())
	//	{
	//		delete search.second;
	//		mComponents.erase(search);
	//	}
	//}

	//template <class T>
	//T* getComponent()
	//{
	//	auto search = mComponents.find(typeid(T));
	//	if (search != mComponents.end())
	//	{
	//		return search.second;
	//	}
	//	return nullptr;
	//}
	template <class T>
	T* addComponent();
	template <class T>
	void removeComponent();
	template <class T>
	T* getComponent();
private:
	std::unordered_map<std::type_index, Component*> mComponents;
};

template <class T>
T* GameObject::addComponent()
{
	auto pT = new T(*this);
	mComponents.insert({ typeid(T), pT });
	return pT;
}

template <class T>
void GameObject::removeComponent()
{
	auto search = mComponents.find(typeid(T));
	if (search != mComponents.end())
	{
		delete (*search).second;
		mComponents.erase(search);
	}
}

template <class T>
T* GameObject::getComponent()
{
	auto search = mComponents.find(typeid(T));
	if (search != mComponents.end())
	{
		return dynamic_cast<T*>((*search).second);
	}
	return nullptr;
}



