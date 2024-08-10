#include "Scene.h"
#include "Actor.h"
#include "Renderer/Model.h"

#include <algorithm>


void Scene::Update(float dt)
{
	for (auto& actor : m_actors)
	{
		actor->Update(dt);
	}

	std::erase_if(m_actors, [](auto& actor) { return actor->m_destroyed; });

	// collision
	for (auto& actor1 : m_actors)
	{
		for (auto& actor2 : m_actors)
		{
			if (actor1 == actor2 || (actor1->m_destroyed || actor2->m_destroyed)) continue;

			Vector2 direction = actor1->GetTransform().position - actor2->GetTransform().position;
			float distance = direction.Length();
			// float radius = actor1->m_model->GetRadius() + actor2->m_model->GetRadius();

			/*if (distance <= radius)
			{
				actor1->OnCollision(actor2.get());
				actor2->OnCollision(actor1.get());
			}*/
		}
	}
}

void Scene::Draw(Renderer& renderer)
{
	for (auto& actor : m_actors)
	{
		actor->Draw(renderer);
	}

}

void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	actor->m_scene = this;
	m_actors.push_back(std::move(actor));
}

void Scene::RemoveActor(std::unique_ptr<Actor> actor)
{
	actor->m_scene = this;
	m_actors.remove(std::move(actor));
}

void Scene::RemoveAll()
{
	m_actors.clear();
}
