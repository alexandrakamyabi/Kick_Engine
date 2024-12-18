#include <../Engine/Inc/Kick_Engine.h>
#include "GameState.h"

using namespace Kick_Engine;
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    AppConfig config;
    config.appName = L"Hello Shape";

    App& myApp = MainApp();
    myApp.AddState<TriangleState>("TriangleState"); // UP ARROW
    myApp.AddState<SquareState>("SquareState"); // DOWN ARROW
    myApp.AddState<HeartState>("HeartState"); // NUMPAD2
    myApp.AddState<ZeldaState>("ZeldaState"); // NUMPAD3
    myApp.AddState<ArrowState>("ArrowState"); // NUMPAD1
    myApp.Run(config);
    
    return (0);
}