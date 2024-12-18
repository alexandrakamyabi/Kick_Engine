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
    Kick_Engine::Graphics::DirectionalLight mDirectionalLight;
    Kick_Engine::Graphics::StandardEffect mStandardEffect;
    Kick_Engine::Graphics::TerrainEffect mTerrainEffect;
    Kick_Engine::Graphics::ShadowEffect mShadowEffect;

    Kick_Engine::Graphics::RenderGroup mCharacter;
    Kick_Engine::Graphics::RenderGroup mCharacter2;
    Kick_Engine::Graphics::RenderObject mGround;
    Kick_Engine::Graphics::Terrain mTerrain;

    Kick_Engine::Kick_Math::Vector3 mCharacterPosition;
    Kick_Engine::Kick_Math::Vector3 mCharacter2Position;
};