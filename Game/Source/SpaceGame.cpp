#include "SpaceGame.h"
#include "Components/CharacterComponent.h"
#include "Engine.h"

#include <memory>

bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<Scene>(m_engine);

	ADD_OBSERVER(PlayerDead, SpaceGame::OnPlayerDead);
	ADD_OBSERVER(AddPoints, SpaceGame::OnAddPoints);
	ADD_OBSERVER(EnemyRespawn, SpaceGame::OnEnemyRespawn);
	ADD_OBSERVER(IncreaseDamage, SpaceGame::OnCollectSuper);

	return true;
}

void SpaceGame::Update(float dt)
{
    
    switch (m_state)
    {
    case SpaceGame::State::INIT:
    {
        m_scene->RemoveAll();

        rapidjson::Document document;
        Json::Load("scenes/title.json", document);
        m_scene->Read(document);
        m_scene->Initialize();

        m_state = SpaceGame::State::TITLE;
    }
        break;
    case SpaceGame::State::TITLE:
        if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
        {
            std::string sceneNames[] = { "Scenes/tilemap.json", "scenes/game.json" };
            for (auto sceneName : sceneNames)
            {
                rapidjson::Document document;
                Json::Load(sceneName, document);
                m_scene->Read(document);
            }
            m_scene->Initialize();
            m_state = State::START_GAME;
        }
        break;
    case SpaceGame::State::START_GAME:
    {
        EVENT_NOTIFY(EnemyRespawn);
        m_state = State::GAME;
    }
        break;
    case SpaceGame::State::GAME:
    {
        if (instanceCreatedCount == 3)
        {
            instanceCreatedCount = 0;
            auto super = Factory::Instance().Create<Actor>("super");
            super->transform.position = Vector2{ randomf(300, 500), randomf(400) };
            m_scene->AddActor(std::move(super), true);
            EVENT_NOTIFY(IncreaseDamage);
            m_state = State::GAME;
        }
        if (m_scene->GetActor<Actor>("player")->GetComponent<CharacterComponent>()->health <= 0)
        {
            m_state = State::GAME_OVER;
        }
    }
    break;
    case  SpaceGame::State::GAME_OVER:
    {
        m_scene->RemoveAll();

        rapidjson::Document document;
        Json::Load("scenes/endGame.json", document);
        m_scene->Read(document);
        m_scene->Initialize();
        m_state = State::GAME_OVER_WAIT;
        m_stateTimer = 3;
    }
        break;
    case SpaceGame::State::GAME_OVER_WAIT:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_state = State::INIT;
        }
        break;
    default:
        break;
    }
     //if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
     //{
     //    m_scene->RemoveAll();
     //}

	m_scene->Update(dt);
}

void SpaceGame::Draw(Renderer& renderer)
{
    m_scene->Draw(renderer);

    switch (m_state)
    {
    case SpaceGame::State::TITLE:
        // draw text "Game Title"
        
        break;
    case SpaceGame::State::GAME_OVER:
        // draw text "Game Over"
        
        break;
    default:
        break;
    }

    //// draw score
    //std::string text = "Score " + std::to_string(m_score);
    //// draw lives
    //text = "Lives " + std::to_string(m_lives);
    m_scene->Draw(renderer);
}

void SpaceGame::OnPlayerDead(const Event& event)
{
	std::cout << "game player has been VANQUISHED!";
}



void SpaceGame::OnAddPoints(const Event& event)
{
	m_score += std::get<int>(event.data);
	std::cout << m_score << std::endl;
}

void SpaceGame::OnEnemyRespawn(const Event& event)
{
    auto enemy = Factory::Instance().Create<Actor>("enemy");
    enemy->transform.position = Vector2{ randomf(300, 500), randomf(400) };
    m_scene->AddActor(std::move(enemy), true);

    instanceCreatedCount++;
}
void SpaceGame::OnCollectSuper(const Event& event)
{
    if (m_scene->GetActor<Actor>("player"))
    {
        AddDamage(25);
    }
}

bool SpaceGame::Shutdown()
{
	m_scene->RemoveAll(true);

    return false;
}