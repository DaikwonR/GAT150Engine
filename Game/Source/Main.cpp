#include "Engine.h"
#include "SpaceGame.h"

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << endl;

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>(engine.get());
	game->Initialize();
	

#pragma region Json contents

	// !! code not necessary, it just shows the contents
	// of the file !!
	// std::string buffer;
	// File::ReadFile("Scenes/scene.json", buffer);
	// show the contents of the json file
	// cout << buffer;
#pragma endregion

	while (!engine->IsQuit())
	{
		// update
		engine->Update();
		game->Update(engine->GetTime().GetDeltaTime());

		// render
		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();

		game->Draw(engine->GetRenderer());

		// draw
		
		// end frame
		engine->GetRenderer().EndFrame();

	}

	game->Shutdown();
	ResourceManager::Instance().Clear();
	engine->ShutDown();

	return 0;
}