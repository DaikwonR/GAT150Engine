#pragma once

class Engine;
class Renderer;
class Scene;

class Game
{
public:
	Game() = default;
	Game(Engine* engine) : m_engine{ engine } {}

	virtual bool Initialize() = 0;
	virtual bool Shutdown() = 0;

	virtual void Update(float dt) = 0;
	virtual void Draw(Renderer& renderer) = 0;

	int GetScore() const { return m_score; }
	void AddPoints(int points) { m_score += points; }
    void AddDamage(int dps) { m_dps += dps; }

	int GetLives() const { return m_lives; }
	void SetLives(int lives) { m_lives = lives; }

protected:
	int m_score = 0;
	int m_lives = 0;
    int m_dps = 0;

	Engine* m_engine{ nullptr };
};