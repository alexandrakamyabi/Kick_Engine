#pragma once
#include <../Kick_Engine/Inc/Kick_Engine.h>


class GameState : public Kick_Engine::AppState
{
public:
    ~GameState() = default;
    void Initialize() override;
    void Terminate() override;
    void Render() override;
    void Update(float deltaTime) override;
    void DebugUI() override;

private:

    Kick_Engine::GameWorld mGameWorld;

};