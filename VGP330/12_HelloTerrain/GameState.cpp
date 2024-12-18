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
    mStandardEffect.SetLightCamera(mShadowEffect.GetLightCamera());
    mStandardEffect.SetShadowMap(mShadowEffect.GetDepthMap());

    mTerrainEffect.Initialize();
    mTerrainEffect.SetCamera(mCamera);
    mTerrainEffect.SetDirectionalLight(mDirectionalLight);
    mTerrainEffect.SetLightCamera(mShadowEffect.GetLightCamera());
    mTerrainEffect.SetShadowMap(mShadowEffect.GetDepthMap());

    mShadowEffect.Initialize();
    mShadowEffect.SetDirectionalLight(mDirectionalLight);

    ModelId modelId = ModelManager::Get()->LoadModel(L"../../Assets/Models/character/character.model");
    mCharacter = CreateRenderGroup(modelId);

    ModelId modelId2 = ModelManager::Get()->LoadModel(L"../../Assets/Models/character/character2.model");
    mCharacter2 = CreateRenderGroup(modelId2);


    mTerrain.Initialize(L"../../Assets/Textures/terrain/heightmap_512x512.raw", 20.0f);

    
    mGround.meshBuffer.Initialize(mTerrain.GetMesh());
    mGround.diffuseMapId = TextureManager::Get()->LoadTexture(L"terrain/dirt_seamless.jpg");
    mGround.bumpMapId = TextureManager::Get()->LoadTexture(L"terrain/grass_2048.jpg");

    mCharacterPosition.x = 10.0f;
    mCharacterPosition.z = 10.0f;
    mCharacterPosition.y = mTerrain.GetHeight(mCharacterPosition);
    SetRenderGroupPosition(mCharacter, mCharacterPosition);

    mCharacter2Position.x = 5.0f;
    mCharacter2Position.z = 15.0f;
    mCharacter2Position.y = mTerrain.GetHeight(mCharacter2Position);
    SetRenderGroupPosition(mCharacter2, mCharacter2Position);


};
void GameState::Terminate()
{
    mGround.Terminate();
    CleanupRenderGroup(mCharacter);
    CleanupRenderGroup(mCharacter2);
    mStandardEffect.Terminate();
}
void GameState::Render()
{
    mShadowEffect.Begin();
        DrawRenderGroup(mShadowEffect, mCharacter);
        DrawRenderGroup(mShadowEffect, mCharacter2);
    mShadowEffect.End();

    mTerrainEffect.Begin();
        mTerrainEffect.Render(mGround);
    mTerrainEffect.End();

    mStandardEffect.Begin();
        DrawRenderGroup(mStandardEffect, mCharacter);
        DrawRenderGroup(mStandardEffect, mCharacter2);
    mStandardEffect.End();
}
void GameState::Update(float deltaTime)
{
    UpdateCameraControl(deltaTime);
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

    float terrainWidth = mTerrain.GetWidth();
    float terrainHeight = mTerrain.GetHeight();
    if (ImGui::CollapsingHeader("CharacterPosition", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::DragFloat3("PosX##Character", &mCharacterPosition.x, 0.1f, 0.0f, terrainWidth))
        {
            mCharacterPosition.y = mTerrain.GetHeight(mCharacterPosition);
            SetRenderGroupPosition(mCharacter, mCharacterPosition);
        }
        if (ImGui::DragFloat3("PosZ##Character", &mCharacterPosition.x, 0.1f, 0.0f, terrainHeight))
        {
            mCharacterPosition.y = mTerrain.GetHeight(mCharacter2Position);
            SetRenderGroupPosition(mCharacter2, mCharacterPosition);
        }
    }

    if (ImGui::CollapsingHeader("Character2Position", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::DragFloat3("PosX##Character2", &mCharacter2Position.x, 0.1f, 0.0f, terrainWidth))
        {
            mCharacterPosition.y = mTerrain.GetHeight(mCharacterPosition);
            SetRenderGroupPosition(mCharacter, mCharacterPosition);
        }
        if (ImGui::DragFloat3("PosX##Character2", &mCharacter2Position.x, 0.1f, 0.0f, terrainHeight))
        {
            mCharacterPosition.y = mTerrain.GetHeight(mCharacter2Position);
            SetRenderGroupPosition(mCharacter2, mCharacterPosition);
        }
    }
    mStandardEffect.DebugUI();
    mShadowEffect.DebugUI();
    mTerrainEffect.DebugUI();
    ImGui::End();
    SimpleDraw::AddGroundPlane(20.0f, Colors::White);
    SimpleDraw::Render(mCamera);
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

    //walking on terrrain map
    float characterHeight = 3.0f;
    Kick_Math::Vector3 cameraPos = mCamera.GetPosition();
    cameraPos.y = mTerrain.GetHeight(cameraPos) + characterHeight;
    mCamera.SetPosition(cameraPos);
}