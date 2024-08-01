#include "../Source/Framework/Engine.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cassert>



using namespace std;

int main(int argc, char* argv[])
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();


	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << endl;
	
	// text->Create(g_engine.GetRenderer(), "Hello World", Color{ 1, 1, 1, 1 });

	while (!engine->IsQuit())
	{
		engine->Update();
		
		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();
		
		engine->GetPS().Draw(engine->GetRenderer());
		
		engine->GetRenderer().EndFrame();


	}

	engine->ShutDown();
	return 0;
}