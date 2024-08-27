#include "CharacterComponent.h"
#include "Engine.h"

FACTORY_REGISTER(CharacterComponent)

void CharacterComponent::Initialize()
{
    owner->OnCollisionEnter = std::bind(&CharacterComponent::OnCollisionEnter, this, std::placeholders::_1);
    owner->OnCollisionExit = std::bind(&CharacterComponent::OnCollisionExit, this, std::placeholders::_1);
}

void CharacterComponent::Update(float dt)
{
    Vector2 direction{ 0, 0 };
    if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
    if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;
    owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * speed * 10);

    if (grounded && owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
    {
        owner->GetComponent<PhysicsComponent>()->SetVelocity(Vector2{ 0, -500 });
    }

    if (owner->scene->engine->GetInput().GetMouseButDown(SDL_BUTTON_LEFT))
    {
        
    }
}

void CharacterComponent::OnCollisionEnter(Actor* actor)
{
    // std::cout << "Player went bye bye!\n" << endl;

    //EVENT_NOTIFY(PlayerDead);
    //EVENT_NOTIFY_DATA(AddPoints, 100);

    if (actor->tag == "Ground")
    {
        grounded = true;
    }
}

void CharacterComponent::OnCollisionExit(Actor* actor)
{
    if (actor->tag == "Ground")
    {
        grounded = false;
    }
}

int CharacterComponent::takeDamage(Actor* actor)
{

    if (actor->tag == "Hero")

    return health - damage;
}

void CharacterComponent::Read(const json_t& value)
{
    READ_DATA(value, speed);
}

void CharacterComponent::Write(json_t& value)
{
}