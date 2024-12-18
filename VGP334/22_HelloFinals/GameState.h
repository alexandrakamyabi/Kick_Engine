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
    void ChangeAnimation();
    void ChangeToEndAnimation();
    void MoveUP();

    Kick_Engine::Graphics::Camera mCamera;
    Kick_Engine::Graphics::DirectionalLight mDirectionalLight;
    Kick_Engine::Graphics::StandardEffect mStandardEffect;

    Kick_Engine::Graphics::RenderObject mGround;

    Kick_Engine::Graphics::RenderObject mDisco;
    // CHARACTER
    Kick_Engine::Graphics::ModelId mCharacterId;
    Kick_Engine::Graphics::RenderGroup mCharacter;
    Kick_Engine::Graphics::Animator mCharacterAnimator;
    Kick_Engine::Kick_Math::Vector3 mCharacterPosition;

    Kick_Engine::Graphics::ModelId mCharacterId2;
    Kick_Engine::Graphics::RenderGroup mCharacter2;
    Kick_Engine::Graphics::Animator mCharacterAnimator2;
    Kick_Engine::Kick_Math::Vector3 mCharacter2Position;

    // PARTICLE EFFECTS
    Kick_Engine::Graphics::ParticleEffect mParticleEffect;
    Kick_Engine::FireworkParticleSystem mFireworks;
    Kick_Engine::ParticleSystem mSparkles;

    // ANIMATION
    Kick_Engine::Kick_Math::Vector3 mOffset = Kick_Engine::Kick_Math::Vector3::Zero;
    Kick_Engine::Graphics::Animation mAnimation;
    Kick_Engine::Graphics::Animation mAnimationCharacter;
    float mAnimationTime = 0.0f;
    float mAnimationCharacterTime = 0.0f;

    // SOUND
    Kick_Engine::Audio::SoundId mSoundID;

    int mAnimationIndex = -1;
    bool mDrawSkeleton = false;
    float mTime = 0.0f;
};