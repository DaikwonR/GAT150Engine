#pragma once
#include "Engine.h"

class CharacterComponent : public Component
{
public:
    CLASS_DECLARATION(CharacterComponent)
    CLASS_PROTOTYPE(CharacterComponent)

    void Initialize() override;
    void Update(float dt) override;

    void OnCollisionEnter(Actor* actor);
    void OnCollisionExit(Actor* actor);

    int takeDamage(Actor* actor);

    float speed{ 0 };
    bool grounded = false;
    int health{ 100 };
    int damage{ 10 };
};
