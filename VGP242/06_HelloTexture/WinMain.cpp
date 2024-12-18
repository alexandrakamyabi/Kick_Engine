#include <../Engine/Inc/Kick_Engine.h>
#include "GameState.h"

using namespace Kick_Engine;
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    AppConfig config;
    config.appName = L"Hello Texture";

    App& myApp = MainApp();
    myApp.AddState<GameState>("GameState");
    myApp.Run(config);

    return (0);
}