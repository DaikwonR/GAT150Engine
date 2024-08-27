#include "SuperComponent.h"
#include "Engine.h"

FACTORY_REGISTER(SuperComponent)

void SuperComponent::Initialize()
{
    owner->OnCollisionEnter = std::bind(&SuperComponent::OnCollisionEnter, this, std::placeholders::_1);
}

void SuperComponent::Update(float dt)
{

    
}

void SuperComponent::OnCollisionEnter(Actor* actor)
{
    if (!actor->destroyed && (actor->name == "enemy"))
    {
        EVENT_NOTIFY_DATA(AddPoints, 200);
        actor->destroyed = true;
    }
    // std::cout << "Player went bye bye!\n" << endl;
}

void SuperComponent::Read(const json_t& value)
{
    
}

void SuperComponent::Write(json_t& value)
{
}