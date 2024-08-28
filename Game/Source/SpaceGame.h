#pragma once
#include "Framework/Game.h"
#include "Event/EventSystem.h"

#include <memory>

class SpaceGame : public Game, Observer
{

public:
	SpaceGame() = default;
	SpaceGame(Engine* engine) : Game{ engine } {}

	bool Initialize() override;
	bool Shutdown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

	// Events
	void OnPlayerDead(const Event& event);
	void OnAddPoints(const Event& event);
    void OnEnemyRespawn(const Event& event);

private:
	std::unique_ptr<class Scene> m_scene;
};
