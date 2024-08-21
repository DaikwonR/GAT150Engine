#pragma once
#include "Engine.h"

class RocketComponent : public Component
{
public:

	CLASS_DECLARATION(RocketComponent)
	CLASS_PROTOTYPE(RocketComponent)

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);
	
	float speed{ 0 };
};