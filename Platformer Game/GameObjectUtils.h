#pragma once
#include "GameObject.h"
#include <memory>

std::unique_ptr<GameObject> makeUIButton(std::string buttonText);

