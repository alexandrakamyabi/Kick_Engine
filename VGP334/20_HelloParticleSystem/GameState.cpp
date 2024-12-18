#include "GameState.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Kick_Math;
using namespace Kick_Engine::Input;
using namespace Kick_Engine::Audio;

void GameState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 2.0f, -8.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

    mDirectionalLight.direction = Kick_Math::Normalize({ 1.0f,-1.0f,1.0f });
    mDirectionalLight.ambient = { 0.5f, 0.5f,0.5f,1.0f };
    mDirectionalLight.diffuse = { 0.8f, 0.8f,0.8f,1.0f };
    mDirectionalLight.specular = { 1.0f, 1.0f,1.0f,1.0f };

    mParticleEffect.Initialize();
    mParticleEffect.SetCamera(mCamera);

    ParticleSystemInfo info;
    info.spawnPosition = Kick_Math::Vector3::Zero;
    info.spawnDirection = Kick_Math::Vector3::YAxis;
    info.spawnDelay = 0.0f;
    info.systemLifeTime = 99999.0f;
    info.minParticlePerEmit = 3;
    info.maxParticlePerEmit = 5;
    info.minTimeBetweenEmit = 0.1f;
    info.maxTimeBetweenEmit = 0.3f;
    info.minSpawnAngle = -30.0f * 3.141592 / 180.0f;
    info.maxSpawnAngle = 30.0f * 3.141592 / 180.0f;
    info.minSpeed = 5.0f;
    info.maxSpeed = 10.0f;
    info.minLifeTime = 0.3f;
    info.maxLifeTime = 1.0f;
    info.minStartColor = Colors::White;
    info.maxStartColor = Colors::White;
    info.minEndColor = Colors::White;
    info.maxEndColor = Colors::White;
    info.minStartScale = Kick_Math::Vector3::One;
    info.maxStartScale = Kick_Math::Vector3::One;
    info.minEndScale = Kick_Math::Vector3::Zero;
    info.maxEndScale = Kick_Math::Vector3::Zero;
    info.maxParticles = 100;
    info.particleTextureId = TextureManager::Get()->LoadTexture("Images/mushroom.png");
    mParticleSystem.Initialize(info);
    mParticleSystem.SetCamera(mCamera);

    // FIREWORKS
    info.spawnPosition = {0.0f, 0.0f, 10.0f};
    info.spawnDirection = Kick_Math::Vector3::YAxis;
    info.spawnDelay = 0.0f;
    info.systemLifeTime = 99999.0f;
    info.minParticlePerEmit = 1;
    info.maxParticlePerEmit = 3;
    info.minTimeBetweenEmit = 0.5f;
    info.maxTimeBetweenEmit = 2.0f;
    info.minSpawnAngle = -10.0f * 3.141592 / 180.0f;
    info.maxSpawnAngle = 10.0f * 3.141592 / 180.0f;
    info.minSpeed = 10.0f;
    info.maxSpeed = 15.0f;
    info.minLifeTime = 1.0f;
    info.maxLifeTime = 2.0f;
    info.minStartColor = Colors::White;
    info.maxStartColor = Colors::White;
    info.minEndColor = Colors::OrangeRed;
    info.maxEndColor = Colors::Orange;
    info.minStartScale = Kick_Math::Vector3::One;
    info.maxStartScale = Kick_Math::Vector3::One;
    info.minEndScale = Kick_Math::Vector3::Zero;
    info.maxEndScale = Kick_Math::Vector3::Zero;
    info.maxParticles = 5;
    info.particleTextureId = TextureManager::Get()->LoadTexture("Images/bullet1.png");
    mFireworks.Initialize(info);
    mFireworks.SetCamera(mCamera);

    mExplosionEventId = EventManager::Get()->AddListener(EventType::FireworkExplode, std::bind(&GameState::OnExplosionEvent, this, std::placeholders::_1));
    mSoundId = SoundEffectManager::Get()->Load("explosion.wav");
};
void GameState::Terminate()
{
    EventManager::Get()->RemoveListener(EventType::FireworkExplode, mExplosionEventId);
    mFireworks.Terminate();
    mParticleSystem.Terminate();
    mParticleEffect.Terminate();
}
void GameState::Render()
{
    SimpleDraw::AddGroundPlane(10.0f, Colors::White);
    SimpleDraw::Render(mCamera);

    mParticleEffect.Begin();
        mFireworks.Render(mParticleEffect);
        mParticleSystem.Render(mParticleEffect);
    mParticleEffect.End();

}
void GameState::Update(float deltaTime)
{
    mTime += deltaTime;
    mFireworks.Update(deltaTime);
    mParticleSystem.Update(deltaTime);
    UpdateCameraControl(deltaTime);
    auto input = Input::InputSystem::Get();
    if (input->IsKeyPressed(KeyCode::SPACE))
    {
        SoundEffectManager::Get()->Play(mSoundId);
    }
}
void GameState::DebugUI()
{
    ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.01f))
        {
            mDirectionalLight.direction = Kick_Math::Normalize(mDirectionalLight.direction);
        }

        ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
        ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
        ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
    }
    mParticleSystem.DebugUI();
    Physics::PhysicsWorld::Get()->DebugUI();

    ImGui::End();
}

void GameState::OnExplosionEvent(const Kick_Engine::Event* e)
{
    SoundEffectManager::Get()->Play(mSoundId);
}

void GameState::UpdateCameraControl(float deltaTime)
{
    auto input = Input::InputSystem::Get();
    const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
    const float turnSpeed = 0.1f;

    if (input->IsKeyDown(KeyCode::W))
    {
        mCamera.Walk(moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::S))
    {
        mCamera.Walk(-moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::D))
    {
        mCamera.Strafe(moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::A))
    {
        mCamera.Strafe(-moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::E))
    {
        mCamera.Rise(moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::Q))
    {
        mCamera.Rise(-moveSpeed * deltaTime);
    }
    if (input->IsMouseDown(MouseButton::RBUTTON))
    {
        mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
        mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
    }
}