#pragma once
#include "Engine.h"
#include "PlayerComponent.h"

class SuperComponent : public Component
{
public:

    CLASS_DECLARATION(SuperComponent)
    CLASS_PROTOTYPE(SuperComponent)

    void Initialize() override;
    void Update(float dt) override;

    void OnCollisionEnter(Actor* actor);

    PlayerComponent* playerComponent{ nullptr };
};