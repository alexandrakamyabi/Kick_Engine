#include "GameState.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Kick_Math;
using namespace Kick_Engine::Input;

void GameState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 1.0f, -4.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

    mDirectionalLight.direction = Kick_Math::Normalize({ 1.0f,-1.0f,1.0f });
    mDirectionalLight.ambient = { 0.5f, 0.5f,0.5f,1.0f };
    mDirectionalLight.diffuse = { 0.8f, 0.8f,0.8f,1.0f };
    mDirectionalLight.specular = { 1.0f, 1.0f,1.0f,1.0f };

    mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
    mStandardEffect.SetCamera(mCamera);
    mStandardEffect.SetDirectionalLight(mDirectionalLight);

    Mesh ball = MeshBuilder::CreateSphere(60, 60, 0.5f);
    mBall.meshBuffer.Initialize(ball);
    mBall.diffuseMapId = TextureManager::Get()->LoadTexture("Images/misc/basketball.jpg");

    Mesh ground = MeshBuilder::CreateGroundPlane(10, 10, 1.0f);
    mGround.meshBuffer.Initialize(ground);
    mGround.diffuseMapId = TextureManager::Get()->LoadTexture("Images/misc/concrete.jpg");

    AnimationCallback cb = [&]() {MoveRight(); };
    mAnimation = AnimationBuilder()
        .AddPositionKey({ 0.0f, 5.0f, 0.0f}, 0.0f, EaseType::EaseInOutQuad)
        .AddPositionKey({ 0.0f, 0.5f, 0.0f}, 1.0f, EaseType::EaseInQuad)
        .AddPositionKey({ 0.0f, 0.5f, 0.0f}, 1.1f)
        .AddPositionKey({ 0.0f, 5.0f, 0.0f}, 2.0f, EaseType::EaseOutQuad)
        .AddRotationKey({ 0.0f, 0.0f, 0.0f, 1.0f}, 0.0f)
        .AddRotationKey(Kick_Math::Quaternion::Normalize({ 6.28f, 0.0f, 0.0f, 1.0f}), 2.0f)
        .AddScaleKey({ 1.0f, 1.0f, 1.0f}, 0.0f)
        .AddScaleKey({ 1.0f, 1.0f, 1.0f}, 0.8f)
        .AddScaleKey({ 1.0f, 0.25f, 1.0f}, 1.0f)
        .AddScaleKey({ 1.0f, 1.5f, 1.0f}, 1.25f)
        .AddScaleKey({ 1.0f, 1.0f, 1.0f}, 2.0f)
        .AddEventKey(cb, 1.5f)
        .Build();

    mAnimationTime = 0.0f;

    EventManager::Get()->AddListener(EventType::SpacePressed, std::bind(&GameState::OnSpacePressedEvent, this, std::placeholders::_1));
};
void GameState::Terminate()
{
    //EventManager::Get()->RemoveListener(EventType::SpacePressed, std::bind(&GameState::OnSpacePressedEvent, this, std::placeholders::_1));
    mGround.Terminate();
    mBall.Terminate();
    mStandardEffect.Terminate();
}
void GameState::Render()
{
    SimpleDraw::AddGroundPlane(10.0f, Colors::White);
    SimpleDraw::Render(mCamera);

    mBall.transform = mAnimation.GetTransform(mAnimationTime);
    mBall.transform.position += mOffset;
    mStandardEffect.Begin();
        mStandardEffect.Render(mGround);
        mStandardEffect.Render(mBall);
    mStandardEffect.End();
}
void GameState::Update(float deltaTime)
{
    UpdateCameraControl(deltaTime);

    if (Input::InputSystem::Get()->IsKeyPressed(Input::KeyCode::SPACE))
    {
        SpacePressedEvent event;
        EventManager::Broadcast(&event);
    }

    float prevTime = mAnimationTime;
    mAnimationTime += deltaTime;
    while (mAnimationTime > mAnimation.GetDuration())
    {
        mAnimationTime -= mAnimation.GetDuration();
    }
    mAnimation.PlayEvents(prevTime, mAnimationTime);
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

    mStandardEffect.DebugUI();
    ImGui::End();
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

void GameState::MoveRight()
{
    mOffset.x += 1.0f;
}

void GameState::OnSpacePressedEvent(const Kick_Engine::Event* event)
{
    SpacePressedEvent* spEvent = (SpacePressedEvent*)event;
    mOffset.z += 1.0f;
}
