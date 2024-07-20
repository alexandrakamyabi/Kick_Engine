#include <Kick_Engine/Inc/Kick_Engine.h>
#include "GameState.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    // CONFIG
    Kick_Engine::AppConfig myAppConfig;
    myAppConfig.appName = L"Hello Quaternion";

    // APPLICATION
    Kick_Engine::App& myApplication = Kick_Engine::MainApp();
    myApplication.AddState<GameState>("GameState");

    // RUNTIME
    myApplication.Run(myAppConfig);

    return EXIT_SUCCESS;
}