#include "PlayerComponent.h"
#include "Engine.h"

void PlayerComponent::Initialize()
{

}

void PlayerComponent::Update(float dt)
{
	Vector2 dircetion{ 0, 0};
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) dircetion.x = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) dircetion.x = 1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W)) dircetion.x = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_S)) dircetion.x = 1;

	owner->GetComponent<PhysicsComponent>()->ApplyForce(dircetion * speed);
}

void PlayerComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void PlayerComponent::Write(json_t& value)
{
}