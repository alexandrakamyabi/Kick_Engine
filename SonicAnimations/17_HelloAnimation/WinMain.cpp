#include <Kick_Engine/Inc/Kick_Engine.h>

#include "GameState.h"

using namespace Kick_Engine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	App& myApp = Kick_Engine::MainApp();
	myApp.AddState<MainState>("MainState");

	AppConfig config;
	config.appName = L"Hello Light";

	myApp.Run(config);

	return(0);
}