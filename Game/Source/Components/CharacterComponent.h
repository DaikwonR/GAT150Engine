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
    int groundCount{ 0 };

    class PhysicsComponent* physics{ nullptr };
    class TextureAnimationComponent* animation{ nullptr };

    int health{ 100 };
    int damage{ 10 };
};
