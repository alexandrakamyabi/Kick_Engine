#pragma once

#include "Inc/AppState.h"

using namespace Kick_Engine;

class GameState : public AppState
{
public:
    void Initialize();
    void Terminate(){}
    void Update(float deltaTime);  // read input and GraphicsSystem::Get->SetClearColor(Colors::red)...press another, set another color
    void Render(){}
    void DebugUI(){}
};
