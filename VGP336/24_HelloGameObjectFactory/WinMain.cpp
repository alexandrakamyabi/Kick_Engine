#include <../Kick_Engine/Inc/Kick_Engine.h>
#include "GameState.h"



int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    Kick_Engine::App& mainApp = Kick_Engine::MainApp();
    mainApp.AddState<GameState>("GameState");

    mainApp.ChangeState("GameState");

    Kick_Engine::AppConfig config;
    config.appName = L"Hello Game Object Factory";
    config.winWidth = 1280;
    config.winHeight = 780;
    mainApp.Run(config);

    return(0);
}