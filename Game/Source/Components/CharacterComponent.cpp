#include "CharacterComponent.h"
#include "EnemyComponent.h"
#include "Engine.h"

FACTORY_REGISTER(CharacterComponent)

void CharacterComponent::Initialize()
{
    owner->OnCollisionEnter = std::bind(&CharacterComponent::OnCollisionEnter, this, std::placeholders::_1);
    owner->OnCollisionExit = std::bind(&CharacterComponent::OnCollisionExit, this, std::placeholders::_1);

    physics = owner->GetComponent<PhysicsComponent>();
    animation = owner->GetComponent<TextureAnimationComponent>();
}

void CharacterComponent::Update(float dt)
{
    bool onGround = (groundCount > 0);
    Vector2 direction{ 0, 0 };
    if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
    if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

    float modifier = (onGround) ? 1 : 0.2f;
    physics->ApplyForce(direction * speed * modifier * 10);

    if (onGround && owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
    {
        physics->SetVelocity(Vector2{ 0, -500 });
    }

    if (owner->scene->engine->GetInput().GetMouseButDown(0) && !owner->scene->engine->GetInput().GetPrevMouseButDown(0))
    {
        attack = true;
        attackTime = 1;

        // check if touching enemy
        if (enemy)
        {
            auto enemyComponent = enemy->GetComponent<EnemyComponent>();
            if (enemyComponent)
            {
                enemyComponent->health -= damage;
                if (enemyComponent->health <= 0)
                {
                    enemy->destroyed = true;
                    EVENT_NOTIFY(EnemyRespawn);
                }
            }
            // destroy enemy and spawn new one
        }
    }
    
    

    if (health <= 0)
    {
        std::cout << "dead\n";
    }

    attackTime -= dt;
    if (attackTime <= 0)
    {
        attack = false;
    }

    // animations

    if (physics->velocity.x < -0.1f)
    {
        animation->hflip = true;
    }
    else if (physics->velocity.x > 0.1f)
    {
        animation->hflip = false;
    }

    if (attack)
    {
        animation->SetAnimation("attack");
    }
    else
    {
        if (Math::Abs(physics->velocity.x) > 0.1f) animation->SetAnimation("run");
        else animation->SetAnimation("idle");
    }

    
}

void CharacterComponent::OnCollisionEnter(Actor* actor)
{
    // std::cout << "Player went bye bye!\n" << endl;

    //EVENT_NOTIFY(PlayerDead);
    //EVENT_NOTIFY_DATA(AddPoints, 100);
    if (actor->tag == "enemy")
    {
        enemy = actor;
        takeDamage(actor);
    }

    if (actor->tag == "Ground")
    {
        groundCount++;
    }

    if (actor->tag == "super")
    {
        damage += 25;
        actor->destroyed = true;
    }

    std::cout << health << std::endl;
    std::cout << damage << std::endl;
}

void CharacterComponent::OnCollisionExit(Actor* actor)
{
    if (actor == enemy)
    {
        enemy = nullptr;
    }
    if (actor->tag == "Ground")
    {
        groundCount--;
    }

    
}

int CharacterComponent::takeDamage(Actor* actor)
{

    /*if (actor->tag == "enemy")
        health - enemy->OnCollisionEnter;
        if (health == 0)
        {
            return actor->destroyed;
        }*/
    

    return 0;
}

void CharacterComponent::Read(const json_t& value)
{
    READ_DATA(value, speed);
}

void CharacterComponent::Write(json_t& value)
{
}