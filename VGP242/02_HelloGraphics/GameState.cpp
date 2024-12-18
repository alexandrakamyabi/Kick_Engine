#include "GameState.h"
#include "Graphics/Inc/GraphicsSystem.h"
#include "Input/Inc/InputSystem.h"

using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Input;

void GameState::Initialize()
{
    GraphicsSystem::Get()->SetClearColor(Colors::Red);
}
void GameState::Update(float deltaTime)  // read input and GraphicsSystem::Get->SetClearColor(Colors::red)...press another, set another color
{
    if (InputSystem::Get()->IsKeyPressed(Input::KeyCode::UP))
    {
        GraphicsSystem::Get()->SetClearColor(Colors::Blue);
    }
    else if (InputSystem::Get()->IsKeyPressed(Input::KeyCode::DOWN))
    {
        GraphicsSystem::Get()->SetClearColor(Colors::Green);
    }
    else if (InputSystem::Get()->IsKeyPressed(Input::KeyCode::LEFT))
    {
        GraphicsSystem::Get()->SetClearColor(Colors::Yellow);
    }
    else if (InputSystem::Get()->IsKeyPressed(Input::KeyCode::RIGHT))
    {
        GraphicsSystem::Get()->SetClearColor(Colors::Purple);
    }
}
