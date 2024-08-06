#include "Engine.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cassert>

void f()
{
	static int i = 5;
	i++;
	std::cout << i << std::endl;
}

using namespace std;

int main(int argc, char* argv[])
{
	// f();

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << endl;
	
	// create texture, using shared_ptr so texture can be shared
	
	res_t<Texture> texture = ResourceManager::instance().Get<Texture>("beast.png", engine->GetRenderer());
	

	while (!engine->IsQuit())
	{
		engine->Update();
		
		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();
		
		engine->GetPS().Draw(engine->GetRenderer());

		engine->GetRenderer().DrawTexture(texture.get(), 30, 30);
		
		engine->GetRenderer().EndFrame();

	}

	engine->ShutDown();
	return 0;
}