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

    void MoveRight();
    void OnSpacePressedEvent(const Kick_Engine::Event* event);

    Kick_Engine::Graphics::DirectionalLight mDirectionalLight;
    Kick_Engine::Graphics::StandardEffect mStandardEffect;

    Kick_Engine::GameObject mGameObject;
    Kick_Engine::GameWorld mGameWorld;

};