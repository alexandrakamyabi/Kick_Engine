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

    void OnExplosionEvent(const Kick_Engine::Event* e);

private:
    void UpdateCameraControl(float deltaTime);

    Kick_Engine::Graphics::Camera mCamera;
    Kick_Engine::Graphics::DirectionalLight mDirectionalLight;

    Kick_Engine::Graphics::ParticleEffect mParticleEffect;
    Kick_Engine::ParticleSystem mParticleSystem;
    Kick_Engine::FireworkParticleSystem mFireworks;

    Kick_Engine::Audio::SoundId mSoundId;
    std::size_t mExplosionEventId;
    float mTime = 0.0f;
};