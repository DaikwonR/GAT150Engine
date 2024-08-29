#pragma once
#include "Engine.h"

class EnemyComponent : public Component
{
public:
    CLASS_DECLARATION(EnemyComponent)
    CLASS_PROTOTYPE(EnemyComponent)

    void Initialize() override;
    void Update(float dt) override;

    void OnCollisionEnter(Actor* actor);
    void OnCollisionExit(Actor* actor);

    class PhysicsComponent* physics{ nullptr };
    class TextureAnimationComponent* animation{ nullptr };

public:
    float speed = 0;
    int health{ 100 };
    int damage{ 10 };
    bool attack{ false };
    float attackTime{ 0 };
};