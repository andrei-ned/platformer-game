#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "EventFunction.h"
#include <memory>

std::unique_ptr<GameObject> makeUIButton(std::string buttonText);

enum SpikeDirection { Right, Down, Left, Up };

std::unique_ptr<GameObject> makeSpike(EventFunction<Collider&>& onCollisionEvent, SpikeDirection direction, DirectX::SimpleMath::Vector2 pos = DirectX::SimpleMath::Vector2(0,0));
