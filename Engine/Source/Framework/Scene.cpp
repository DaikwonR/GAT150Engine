#include "Engine.h"

#include <algorithm>


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

void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	actor->scene = this;
	m_actors.push_back(std::move(actor));
}

void Scene::RemoveActor(std::unique_ptr<Actor> actor)
{
	actor->scene = this;
	m_actors.remove(std::move(actor));
}

void Scene::RemoveAll()
{
	m_actors.clear();
}

void Scene::Read(const json_t& value)
{
	if (HAS_DATA(value, m_actors) && GET_DATA(value, m_actors).IsArray())
	{
		for (auto& actorValue : GET_DATA(value, m_actors).GetArray())
		{
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->Read(actorValue);

			AddActor(std::move(actor));
		}

	}
}

void Scene::Write(json_t& value)
{
	// 
}

