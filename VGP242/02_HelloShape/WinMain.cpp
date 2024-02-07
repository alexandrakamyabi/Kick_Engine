#include <Kick_Engine/Inc/Kick_Engine.h>

#include "GameState.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ int nCmdShow)
{
	App& myApp = Kick_Engine::MainApp();
	myApp.AddState<TriforceState>("TriforceState");
    myApp.AddState<ChaosEmrald>("ChaosEmrald");
	myApp.AddState<FeeeshState>("FeeeshState");
	myApp.AddState<TriangleState>("TriangleState");

	AppConfig config;
	config.appName = L"Hello Shape :>";

	myApp.Run(config);

	return (0);
}