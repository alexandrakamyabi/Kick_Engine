#include "GameState.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Kick_Math;
using namespace Kick_Engine::Input;

bool NightVision = false;

void GameState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 1.5f, -4.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

    mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
    mStandardEffect.SetCamera(mCamera);
    mStandardEffect.SetDirectionalLight(mDirectionalLight);
    mStandardEffect.SetLightCamera(mShadowEffect.GetLightCamera());
    mStandardEffect.SetShadowMap(mShadowEffect.GetDepthMap());

    mStandardEffectNV.Initialize(L"../../Assets/Shaders/NightVision.fx");
    mStandardEffectNV.SetCamera(mCamera);
    mStandardEffectNV.SetDirectionalLight(mDirectionalLight);
    mStandardEffectNV.SetLightCamera(mShadowEffect.GetLightCamera());
    mStandardEffectNV.SetShadowMap(mShadowEffect.GetDepthMap());

    mTerrainEffect.Initialize();
    mTerrainEffect.SetCamera(mCamera);
    mTerrainEffect.SetDirectionalLight(mDirectionalLight);
    mTerrainEffect.SetLightCamera(mShadowEffect.GetLightCamera());
    mTerrainEffect.SetShadowMap(mShadowEffect.GetDepthMap());

    GraphicsSystem* gs = GraphicsSystem::Get();
    const float screenWidth = gs->GetBackBufferWidth();
    const float screenHeight = gs->GetBackBufferHeight();
    mRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);

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
    mStandardEffectNV.Terminate();
    mRenderTarget.Terminate();
}
void GameState::Update(float deltaTime)
{
    UpdateCameraControl(deltaTime);
}

void GameState::Render()
{
    mTerrainEffect.Begin();
        mTerrainEffect.Render(mGround);
    mTerrainEffect.End();

    //for (auto& renderObject : mCharacter2)
    //{
    //    renderObject.material.emissive = { 0.5f, 1.5f, 0.5f, 1.0f };
    //}

    if (!NightVision)
    {
        GraphicsSystem::Get()->SetClearColor(Colors::Gray);
        mStandardEffect.Begin();
        DrawRenderGroup(mStandardEffect, mCharacter);
        DrawRenderGroup(mStandardEffect, mCharacter2);
        mStandardEffect.End();
    }
    else
    {
        GraphicsSystem::Get()->SetClearColor(Colors::Black);
        mStandardEffectNV.Begin();
        DrawRenderGroup(mStandardEffectNV, mCharacter);
        DrawRenderGroup(mStandardEffectNV, mCharacter2);
        mStandardEffectNV.End();

        //Maybe flash animation

        //mRenderTarget.BeginRender();
        //mStandardEffectNV.Begin();
        //DrawRenderGroup(mStandardEffectNV, mCharacter);
        //DrawRenderGroup(mStandardEffectNV, mCharacter2);
        //mStandardEffectNV.End();
        //mRenderTarget.EndRender();

        ////mBlurRenderTarget.BeginRender({ 0.0f, 0.0f, 0.0f, 0.0f });
        //mBlurRenderTarget.BeginRender();
        //mStandardEffectNV.Begin();
        //DrawRenderGroup(mStandardEffectNV, mCharacter);
        //DrawRenderGroup(mStandardEffectNV, mCharacter2);
        //mStandardEffectNV.End();
        //mBlurRenderTarget.EndRender();

        //mGaussianBlurEffect.Begin();
        //mGaussianBlurEffect.Render(mScreenQuad);
        //mGaussianBlurEffect.End();

        //mPostProcessingEffect.Begin();
        //mPostProcessingEffect.Render(mScreenQuad);
        //mPostProcessingEffect.End();
    }
    }
}

void GameState::DebugUI()
{
    ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::CollapsingHeader("Night Vision", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::Checkbox("UseNightVision", &NightVision))
        {
            NightVision ? 1 : 0;
            if (NightVision)
            {
                mTerrainEffect.ChangeBlend();
            }
            else
            {
                mTerrainEffect.NormalBlend();
            }
        }
    }
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

    float characterHeight = 3.0f;
    Kick_Math::Vector3 cameraPos = mCamera.GetPosition();
    cameraPos.y = mTerrain.GetHeight(cameraPos) + characterHeight;
    mCamera.SetPosition(cameraPos);
}