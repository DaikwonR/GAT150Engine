#pragma once
#include "Object.h"

#include <list>
#include <memory>

class Renderer;
class Actor;
class Game;
class Engine;

class Scene : public Object
{
public:
	Scene(Engine* engine, Game* game = nullptr) : 
		engine{engine }, 
		game { game } {}
	Scene(const Scene& other);

	CLASS_DECLARATION(Scene)
	CLASS_PROTOTYPE(Scene)

	void Initialize() override;
	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(std::unique_ptr<Actor> actor, bool initialize = false);
	void RemoveActor(std::unique_ptr<Actor> actor);
	void RemoveAll(bool force = false);

	template<typename T> T* GetActor();
	template<typename T> T* GetActor(const std::string& name);


public:
	Engine* engine{ nullptr };
	Game* game{ nullptr };

	// void Read(const json_t& value) override;
	// void Write(json_t& value) override;
protected:
	std::list<std::unique_ptr<Actor>> m_actors;


};

template<typename T>
T* Scene::GetActor()
{
	for (auto& actor : m_actors)
	{
		T* result = dynamic_cast<T*>(actor.get());
		if (result) return result;
	}

	return nullptr;
}

template<typename T>
inline T* Scene::GetActor(const std::string& name)
{
	for (auto& actor : m_actors)
	{
		T* result = dynamic_cast<T*>(actor.get());
		if (result && isEqualIgnoreCase(result->name, name)) return result;
	}

	return nullptr;
}
