#include <../Kick_Engine/Inc/Kick_Engine.h>
#include "GameState.h"



int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    Kick_Engine::App& mainApp = Kick_Engine::MainApp();
    mainApp.AddState<GameState>("GameState");

    Kick_Engine::AppConfig config;
    config.appName = L"Hello Particle System";
    config.winWidth = 1280;
    config.winHeight = 780;
    config.debugDrawLimit = 100000;
    mainApp.Run(config);

    return(0);
}