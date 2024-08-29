#pragma once
#include "Engine.h"

class PlayerComponent : public Component
{
public:

	CLASS_DECLARATION(PlayerComponent)
	CLASS_PROTOTYPE(PlayerComponent)

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);
	void OnCollisionExit(Actor* actor);
	
	float speed{ 0 };
    Actor* enemy{ nullptr };
};