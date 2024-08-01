#pragma once

// ** core **
#include "/NU/IntroToGame/GAT150Engine/Engine/Source/Core/EAssert.h"
#include "/NU/IntroToGame/GAT150Engine/Engine/Source/Core/EFile.h"
#include "/NU/IntroToGame/GAT150Engine/Engine/Source/Core/E_Time.h"

// ** systems **
// renderer

#include "/NU/IntroToGame/GAT150Engine/Engine/Source/Renderer/Renderer.h"
#include "/NU/IntroToGame/GAT150Engine/Engine/Source/Renderer/Particle.h"
#include "/NU/IntroToGame/GAT150Engine/Engine/Source/Renderer/ParticleSystem.h"
#include "/NU/IntroToGame/GAT150Engine/Engine/Source/Renderer/Model.h"
#include "/NU/IntroToGame/GAT150Engine/Engine/Source/Renderer/Text.h"
#include "/NU/IntroToGame/GAT150Engine/Engine/Source/Renderer/Font.h"
#include "/NU/IntroToGame/GAT150Engine/Engine/Source/Renderer/Color.h"

// ** import **
#include "/NU/IntroToGame/GAT150Engine/Engine/Source/Input/Input.h"

// ** audio **
#include "/NU/IntroToGame/GAT150Engine/Engine/Source/Audio/Audio.h"

// ** math **
#include "/NU/IntroToGame/GAT150Engine/Engine/Source/Math/Transform.h"
#include "/NU/IntroToGame/GAT150Engine/Engine/Source/Math/MathUtils.h"
#include "/NU/IntroToGame/GAT150Engine/Engine/Source/Math/Vector2.h"
#include "/NU/IntroToGame/GAT150Engine/Engine/Source/Math/Random.h"


#include <fmod.hpp>
#include <SDL.h>
#include <memory>

#define RENDERER g_engine.GetRenderer()
#define INPUT g_engine.GetInput()
#define AUDIO g_engine.GetAudio()

class Engine
{
public:

	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void ShutDown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }
	ParticleSystem& GetPS() { return *m_particleSystem; }

	Time& GetTime() { return *m_time; }
	
	bool IsQuit() { return quit; }
private:
	bool quit{ false };

	std::unique_ptr<Time> m_time;

	std::unique_ptr<Renderer> m_renderer;
	std::unique_ptr<Input> m_input;
	std::unique_ptr<Audio> m_audio;

	std::unique_ptr<ParticleSystem> m_particleSystem;

	static Engine ms_engine;
};

extern Engine g_engine;
