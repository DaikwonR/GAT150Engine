#include "Engine.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cassert>
#include <rapidjson/document.h>

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

	ResourceManager rm = ResourceManager();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << endl;

	std::string s;
	File::ReadFile("text.txt", s);
	cout << s;

	rapidjson::Document document;
	Json::Load("text.txt", document);

	std::string name;
	int age;
	bool isHappy;

	READ_DATA(document, name);
	READ_DATA(document, age);
	READ_DATA(document, isHappy);

	std::cout << name << age << isHappy << std::endl;
	
	// create texture, using shared_ptr so texture can be shared
	
	
	/*res_t<Texture> texture = ResourceManager::instance().Get<Texture>("beast.png", engine->GetRenderer());
	res_t<Font> font = ResourceManager::instance().Get<Font>();
	unique_ptr<Text> text = make_unique<Text>(font);
	text->Create(engine->GetRenderer(), "Hello!", { 1,1,0,1 });*/
	
	Transform t{ {30, 30} };
	unique_ptr<Actor> actor = make_unique<Actor>(t);
	// unique_ptr<Actor> actor = make_unique<Actor>(t);

	while (!engine->IsQuit())
	{
		engine->Update();
		
		// engine->Update(engine->GetTime().GetDeltaTime());

		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();
		// engine->GetRenderer().DrawTexture(texture.get(), randomf(800), randomf(600), randomf(360));
		
		engine->GetPS().Draw(engine->GetRenderer());

		// engine->GetRenderer().DrawTexture(texture.get(), 30, 30);
		
		engine->GetRenderer().EndFrame();

	}

	engine->ShutDown();
	return 0;
}