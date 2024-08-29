#include "EnemyComponent.h"
#include "CharacterComponent.h"
#include "Engine.h"

FACTORY_REGISTER(EnemyComponent)

void EnemyComponent::Initialize()
{
    owner->OnCollisionEnter = std::bind(&EnemyComponent::OnCollisionEnter, this, std::placeholders::_1);
    owner->OnCollisionExit = std::bind(&EnemyComponent::OnCollisionExit, this, std::placeholders::_1);

    physics = owner->GetComponent<PhysicsComponent>();
    animation = owner->GetComponent<TextureAnimationComponent>();
}

void EnemyComponent::Update(float dt)
{
    auto player = owner->scene->GetActor<Actor>("player");
    if (player)
    {
        Vector2 direction{ 0, 0 };
        if (player->transform.position.x < owner->transform.position.x) direction.x = -1;
        if (player->transform.position.x > owner->transform.position.x) direction.x = +1;
        physics->ApplyForce(direction * speed);

        attack = true;
        attackTime = 1;
        
    }

   


    if (physics->velocity.x < -0.1f)
    {
        animation->hflip = true;
    }
    else if (physics->velocity.x > 0.1f)
    {
        animation->hflip = false;
    }

    attackTime -= dt;
    if (attackTime <= 0)
    {
        attack = false;
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

    // std::cout << health << std::endl;

    /*if (owner->scene->engine->GetInput().GetMouseButDown(SDL_BUTTON_LEFT))
    {

    }*/
}
void EnemyComponent::OnCollisionEnter(Actor* actor)
{
    if (actor->name == "player")
    {
        auto characterComponent = actor->GetComponent<CharacterComponent>();
        if (characterComponent)
        {
            // deal damage to player
            characterComponent->health-=damage;
            //if (characterComponent->attack)
            //{
            //    owner->destroyed = true;
            //    auto enemy = Factory::Instance().Create<Actor>("enemy");
            //    enemy->transform.position = Vector2{ randomf(300, 500), randomf(400) };
            //    owner->scene->AddActor(std::move(enemy), true);
            //}
        }
    }
}

void EnemyComponent::OnCollisionExit(Actor* actor)
{
    //if (owner->scene->engine->GetInput().GetMouseButDown(SDL_BUTTON_LEFT))
    //{
    //    if (actor->tag == "enemy" && actor->destroyed)
    //    {
    //        auto bat = Factory::Instance().Create<Actor>("enemy");
    //        bat->transform.position = Vector2{ randomf(300, 500), randomf(400) };
    //        owner->scene->AddActor(std::move(bat), true);
    //    }
    //}
}

void EnemyComponent::Read(const json_t& value)
{
    READ_DATA(value, speed);
}

void EnemyComponent::Write(json_t& value)
{
}