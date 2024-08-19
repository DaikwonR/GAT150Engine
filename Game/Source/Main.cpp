#include "Engine.h"
#include "Components/PlayerComponent.h"

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	Factory::Instance().Register<Actor>("Actor");
	Factory::Instance().Register<TextureComponent>("TextureComponent");
	Factory::Instance().Register<EnginePhysicsComponent>("EnginePhysicsComponent");
	Factory::Instance().Register<PlayerComponent>("PlayerComponent");
	Factory::Instance().Register<TextComponent>("TextComponent");



	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();


	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << endl;

	// !! code not necessary, it just shows the contenst
	// of the file !!
	// std::string buffer;
	// File::ReadFile("Scenes/scene.json", buffer);
	// show the contents of the json file
	// cout << buffer;

	rapidjson::Document document;
	Json::Load("Scenes/scene.json", document);

	std::unique_ptr<Scene> scene = std::make_unique<Scene>(engine.get());
	scene->Read(document);
	scene->Initialize();

	while (!engine->IsQuit())
	{
		// update
		engine->Update();
		scene->Update(engine->GetTime().GetDeltaTime());
		
		auto* actor = scene->GetActor<Actor>("text");
		if (actor)
		{
			actor->transform.scale = Math::Abs(Math::Sin(engine->GetTime().GetTime())) * 5;
			actor->transform.rotation += 90 * engine->GetTime().GetDeltaTime();
		}

		// render
		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();

		// draw
		scene->Draw(engine->GetRenderer());
		
		// end frame
		engine->GetRenderer().EndFrame();

	}

	scene->RemoveAll();
	ResourceManager::Instance().Clear();
	engine->ShutDown();

	return 0;
}