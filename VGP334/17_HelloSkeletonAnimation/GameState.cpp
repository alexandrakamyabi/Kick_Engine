#include "GameState.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Kick_Math;
using namespace Kick_Engine::Input;

void GameState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 2.0f, -4.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

    mDirectionalLight.direction = Kick_Math::Normalize({ 1.0f,-1.0f,1.0f });
    mDirectionalLight.ambient = { 0.5f, 0.5f,0.5f,1.0f };
    mDirectionalLight.diffuse = { 0.8f, 0.8f,0.8f,1.0f };
    mDirectionalLight.specular = { 1.0f, 1.0f,1.0f,1.0f };

    mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
    mStandardEffect.SetCamera(mCamera);
    mStandardEffect.SetDirectionalLight(mDirectionalLight);

    Mesh ground = MeshBuilder::CreateGroundPlane(10, 10, 1.0f);
    mGround.meshBuffer.Initialize(ground);
    mGround.diffuseMapId = TextureManager::Get()->LoadTexture("Images/misc/concrete.jpg");

    mCharacterId = ModelManager::Get()->LoadModel("../../Assets/Models/character/character.model");
    ModelManager::Get()->AddAnimation(mCharacterId, "../../Assets/Models/character/rumbadance.model");
    ModelManager::Get()->AddAnimation(mCharacterId, "../../Assets/Models/character/mutant_turn.model");
    ModelManager::Get()->AddAnimation(mCharacterId, "../../Assets/Models/character/walkfoward.model");
    mCharacter = CreateRenderGroup(mCharacterId, &mCharacterAnimator);
    mCharacterAnimator.Initialize(mCharacterId);
    mCharacterAnimator.PlayAnimation(1, true);

};
void GameState::Terminate()
{
    CleanupRenderGroup(mCharacter);
    mGround.Terminate();
    mStandardEffect.Terminate();
}
void GameState::Render()
{
    SimpleDraw::AddGroundPlane(10.0f, Colors::White);
    SimpleDraw::Render(mCamera);


    mStandardEffect.Begin();
    if (mDrawSkeleton)
    {
        AnimationUtil::BoneTransforms boneTransforms;
        AnimationUtil::ComputerBoneTransform(mCharacterId, boneTransforms, &mCharacterAnimator);
        AnimationUtil::DrawSkeleton(mCharacterId, boneTransforms);
    }
    else
    {
        DrawRenderGroup(mStandardEffect, mCharacter);
    }
        mStandardEffect.Render(mGround);
    mStandardEffect.End();
}
void GameState::Update(float deltaTime)
{
    UpdateCameraControl(deltaTime);
    mCharacterAnimator.Update(deltaTime);
    //auto input = Input::InputSystem::Get();
    //int targetAnim = mAnimationIndex;
    //if (input->IsKeyPressed(Input::KeyCode::UP))
    //{
    //    targetAnim = 0;
    //}
    //else if (input->IsKeyPressed(Input::KeyCode::DOWN))
    //{
    //    targetAnim = 1;
    //}
    //else if (input->IsKeyPressed(Input::KeyCode::LEFT))
    //{
    //    targetAnim = 2;
    //}
    //else if (input->IsKeyPressed(Input::KeyCode::RIGHT))
    //{
    //    targetAnim = 3;
    //}

    //if (targetAnim != mAnimationIndex)
    //{
    //    mAnimationIndex = targetAnim;
    //    mCharacterAnimator.PlayAnimation(mAnimationIndex, true);
    //}
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

        if (ImGui::DragInt("AnimationIndex", &mAnimationIndex, 1, -1, mCharacterAnimator.GetAnimationCount() - 1))
        {
            mCharacterAnimator.PlayAnimation(mAnimationIndex, true);
        }
    }
    mStandardEffect.DebugUI();
    ImGui::Checkbox("DrawSkeleton", &mDrawSkeleton);
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