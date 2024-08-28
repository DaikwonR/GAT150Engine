#pragma once

// ** core **
#include "Core/EAssert.h"
#include "Core/EFile.h"
#include "Core/E_Time.h"
#include "Core/EString.h"
#include "Core/Json.h"
#include "Core/Singleton.h"
#include "Core/Factory.h"

// ** systems **
// renderer
#include "Renderer/Renderer.h"
#include "Renderer/Particle.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Model.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Renderer/Color.h"
#include "Renderer/Texture.h"

// ** framework **
#include "Framework/Actor.h"
#include "Framework/Game.h"
#include "Framework/Object.h"
#include "Framework/Scene.h"

// ** import **
#include "Input/Input.h"
			   
// ** audio ** 
#include "Audio/Audio.h"

// ** math **
#include "Math/Transform.h"
#include "Math/MathUtils.h"
#include "Math/Vector2.h"
#include "Math/Random.h"
#include "Math/Rect.h"

// ** event **
#include "Event/Event.h"
#include "Event/EventSystem.h"
#include "Event/Observer.h"

// ** resources **
#include "../Source/Resources/Resource.h"
#include "../Source/Resources/ResourceManager.h"

// ** components **
#include "Components/Component.h"
#include "Components/RenderComponent.h"
#include "Components/TextureComponent.h"
#include "Components/TextureAnimationComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/EnginePhysicsComponent.h"
#include "Components/TextComponent.h"

// ** physics **
#include "Physics/Physics.h"

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
	
	Physics& GetPhysics() { return *m_physics; }

	bool IsQuit() { return quit; }

private:
	bool quit{ false };

	std::unique_ptr<Time> m_time;

	std::unique_ptr<Renderer> m_renderer;
	std::unique_ptr<Input> m_input;
	std::unique_ptr<Audio> m_audio;

	std::unique_ptr<ParticleSystem> m_particleSystem;

	std::unique_ptr<Physics> m_physics;

	static Engine ms_engine;
};

extern Engine g_engine;
