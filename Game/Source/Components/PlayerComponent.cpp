#include "PlayerComponent.h"
#include "Engine.h"

FACTORY_REGISTER(PlayerComponent)

void PlayerComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1);
}

void PlayerComponent::Update(float dt)
{
	Vector2 dircetion{ 0, 0};
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) dircetion.x = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) dircetion.x = 1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W)) dircetion.x = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_S)) dircetion.x = 1;

	owner->GetComponent<PhysicsComponent>()->ApplyForce(dircetion * speed);

	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_S))
	{
		auto rocket = Factory::Instance().Create<Actor>("rocket");
		rocket->transform.position = owner->transform.position;
		rocket->transform.rotation = owner->transform.rotation;
		owner->scene->AddActor(std::move(rocket), true);

		

	}
}

void PlayerComponent::OnCollisionEnter(Actor* actor)
{
	// std::cout << "Player went bye bye!\n" << endl;
}

void PlayerComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void PlayerComponent::Write(json_t& value)
{
}