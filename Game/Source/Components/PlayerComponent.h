#pragma once
#include "Engine.h"

class PlayerComponent : public Component
{
public:

	CLASS_DECLARATION(PlayerComponent)

	void Initialize() override;
	void Update(float dt) override;
	
	float speed{ 0 };
};