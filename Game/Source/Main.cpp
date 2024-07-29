#include "Engine.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>




using namespace std;

int main(int argc, char* argv[])
{
	g_engine.Initialize();

	// text->Create(g_engine.GetRenderer(), "Hello World", Color{ 1, 1, 1, 1 });

	while (!g_engine.IsQuit())
	{
		g_engine.Update();
		

		g_engine.GetRenderer().SetColor(random(255), random(255), random(255), 0);
		g_engine.GetRenderer().BeginFrame();

		g_engine.GetPS().Draw(g_engine.GetRenderer());

		g_engine.GetRenderer().EndFrame();


	}

	g_engine.ShutDown();
	return 0;
}