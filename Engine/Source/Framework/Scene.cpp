#include "Engine.h"
#include "Actor.h"
#include "Core/Factory.h"
#include "Core/EAssert.h"
#include "Components/CollisionComponent.h"

#include <algorithm>


Scene::Scene(const Scene& other)
{
	// ASSERT(false);
}

void Scene::Initialize()
{
	for (auto& actor : m_actors)
	{
		actor->Initialize();
	}
}

void Scene::Update(float dt)
{
	for (auto& actor : m_actors)
	{
		if (actor->active)
		{
		actor->Update(dt);

		}
	}

	// destroy
	std::erase_if(m_actors, [](auto& actor) { return actor->destroyed; });

}

void Scene::Draw(Renderer& renderer)
{
	for (auto& actor : m_actors)
	{
		if (actor->active)
		{
		actor->Draw(renderer);

		}
	}

}

void Scene::AddActor(std::unique_ptr<Actor> actor, bool initialize)
{
	actor->scene = this;
	if (initialize) actor->Initialize();

	m_actors.push_back(std::move(actor));
}

void Scene::RemoveActor(std::unique_ptr<Actor> actor)
{
	actor->scene = this;
	m_actors.remove(std::move(actor));
}

void Scene::RemoveAll(bool force)
{
    std::erase_if(m_actors, [force](auto& actor) { return (force || (!actor->persistent));
});
	
}



void Scene::Read(const json_t& value)
{
	if (HAS_DATA(value, m_actors) && GET_DATA(value, m_actors).IsArray())
	{
		for (auto& actorValue : GET_DATA(value, m_actors).GetArray())
		{
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->Read(actorValue);

			bool prototype = false;
			READ_DATA(actorValue, prototype);

			if (prototype)
			{
				std::string name = actor->name;
				Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
			}
			else
			{
				AddActor(std::move(actor));

			}
		}

	}
}

void Scene::Write(json_t& value)
{
	// 
}

