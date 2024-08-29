#pragma once
#include "Framework/Game.h"
#include "Event/EventSystem.h"
#include "Engine.h"

#include <memory>

class SpaceGame : public Game, Observer
{
public:
    enum class State
    {
        INIT,
        TITLE,
        START_GAME,
        GAME,
        START_LEVEL,
        GAME_OVER,
        GAME_OVER_WAIT
    };
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
    void OnCollectSuper(const Event& event);

private:
    State m_state{ State::INIT };

    float m_spawnTimer{ 0 };
    float m_spawnTime{ 0 };
    float m_stateTimer{ 0 };
    int instanceCreatedCount = 2;
    
    TextComponent* m_textScore{ nullptr };
    TextComponent* m_textTitle{ nullptr };
    Audio* m_audio{ nullptr };

	std::unique_ptr<class Scene> m_scene;
};
