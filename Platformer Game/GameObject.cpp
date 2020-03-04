#include "GameObject.h"
#include <cassert>
#include <algorithm>
#include "Helpers.h"
#include "GameConstants.h"

GameObject::GameObject() : mPos(0, 0), mScale(1, 1), mRotation(0), mOrigin(0, 0), mColor(Colors::White.v) {}
