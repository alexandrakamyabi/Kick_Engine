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
    void UpdateCameraControl(float deltaTime);

    Kick_Engine::Graphics::Camera mCamera;
    Kick_Engine::Graphics::BillboardEffect mBillboardEffect;
    Kick_Engine::Graphics::RenderObject mSprite;
    Kick_Engine::Graphics::BlendState mBlendState;
};