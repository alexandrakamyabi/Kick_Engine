#include "GameState.h"

using namespace Kick_Engine::Graphics;
using namespace Kick_Engine;
using namespace Kick_Engine::Input;

void GameState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 50.0f, -250.0f });
    mCamera.SetLookAt({0.0f, 0.0f, 0.0f});

    // get planet position, have direction offset and distance
    // planetPos = planetPos + (directionOffset * distance)
    //renderTargetCamera.SetPosition(camPos)
    //renderTargetCamera.SetLookAt(planetPos)
    mRenderTargetCamera.SetPosition({ 0.0f, 2.0f, -30.0f });
    mRenderTargetCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
    mRenderTargetCamera.SetAspectRatio(1.0f);

    

    mConstantBuffer.Initialize(sizeof(Matrix4));


    //MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 1.0f);
    //mMeshBuffer.Initialize(sphere);
    //
    //MeshPX skySphere = MeshBuilder::CreateSkySpherePX(100, 100, 1.0f);
    //mSkySphere.Initialize(skySphere);

    std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexturing.fx";
    mVertexShader.Initialize<VertexPX>(shaderFile);
    mPixelShader.Initialize(shaderFile);

    mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
    mWorldTrans = Matrix4::Identity;

    constexpr uint32_t size = 512;
    mRenderTarget.Initialize(size, size, Texture::Format::RGBA_U32);

    //Planet Initialize
    mSkySphere.Initialize();
    mSun.Initialize();

    mMercury.Initialize();
    mMercury.SetPosition({ 20.0f, 0.0f,0.0f });

    mEarth.Initialize();
    mEarth.SetPosition({ 40.0f, 0.0f,0.0f });

    mVenus.Initialize();
    mVenus.SetPosition({ 60.0f, 0.0f,0.0f });

    mMars.Initialize();
    mMars.SetPosition({ 80.0f, 0.0f,0.0f });

    mJupiter.Initialize();
    mJupiter.SetPosition({ 100.0f, 0.0f,0.0f });

    mSaturn.Initialize();
    mSaturn.SetPosition({ 120.0f, 0.0f,0.0f });

    mUranus.Initialize();
    mUranus.SetPosition({ 140.0f, 0.0f,0.0f });

    mNeptune.Initialize();
    mNeptune.SetPosition({ 160.0f, 0.0f,0.0f });



}
void GameState::Terminate()
{
    mSkySphere.Terminate();
    mMercury.Terminate();
    mVenus.Terminate();
    mEarth.Terminate();
    mMars.Terminate();
    mJupiter.Terminate();
    mSaturn.Terminate();
    mUranus.Terminate();
    mNeptune.Terminate();

    mRenderTarget.Terminate();
    mSampler.Terminate();
    //mDiffuseTexture.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();
    //mMeshBuffer.Terminate();
    mConstantBuffer.Terminate();
}

float gRotationY = 0.0f;
float gRotationX = 0.0f;

void GameState::Render()
{
    if (!mDrawWorld)
    {
        return;
    }
    else
    {
        mVertexShader.Bind();
        mPixelShader.Bind();
        //mDiffuseTexture.BindPS(0);
        mSampler.BindPS(0);


        mRenderTarget.BeginRender();
            RenderMesh(mRenderTargetCamera, true);
        mRenderTarget.EndRender();
        RenderMesh(mCamera, true);
        
    }
}

void GameState::RenderMesh(const Camera& camera, bool useTransform)
{
    mSkySphere.Render(camera, mConstantBuffer, useTransform);
    if (mDrawSphereSun)
    {
        mSun.Render(camera, mConstantBuffer, useTransform);
    }
    if (mDrawSphereMercury)
    {
        mMercury.Render(camera, mConstantBuffer, useTransform);
    }
    if (mDrawSphereVenus)
    {
        mVenus.Render(camera, mConstantBuffer, useTransform);
    }
    if (mDrawSphereEarth)
    {
        mEarth.Render(camera, mConstantBuffer, useTransform);
    }
    if (mDrawSphereMars)
    {
        mMars.Render(camera, mConstantBuffer, useTransform);
    }
    if (mDrawSphereJupiter)
    {
        mJupiter.Render(camera, mConstantBuffer, useTransform);
    }
    if (mDrawSphereSaturn)
    {
        mSaturn.Render(camera, mConstantBuffer, useTransform);
    }
    if (mDrawSphereUranus)
    {
        mUranus.Render(camera, mConstantBuffer, useTransform);
    }
    if (mDrawSphereNeptune)
    {
        mNeptune.Render(camera, mConstantBuffer, useTransform);
    }
    //mMeshBuffer.Render();
}
void GameState::Update(float deltaTime)
{
    auto input = InputSystem::Get();
    const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f) * deltaTime;
    const float turnSpeed = 0.1f * deltaTime;
    if (input->IsKeyDown(KeyCode::W))
    {
        mCamera.Walk(moveSpeed);
    }
    else if (input->IsKeyDown(KeyCode::S))
    {
        mCamera.Walk(-moveSpeed);
    }
    if (input->IsKeyDown(KeyCode::D))
    {
        mCamera.Strafe(moveSpeed);
    }
    else if (input->IsKeyDown(KeyCode::A))
    {
        mCamera.Strafe(-moveSpeed);
    }
    if (input->IsKeyDown(KeyCode::E))
    {
        mCamera.Rise(moveSpeed);
    }
    else if (input->IsKeyDown(KeyCode::Q))
    {
        mCamera.Rise(-moveSpeed);
    }
    if (input->IsMouseDown(MouseButton::RBUTTON))
    {
        mCamera.Yaw(input->GetMouseMoveX() * turnSpeed);
        mCamera.Pitch(input->GetMouseMoveY() * turnSpeed);
    }

    //Planet rotations
    mMercury.Update(deltaTime, gRotateMercury);
    mVenus.Update(deltaTime, gRotateVenus);
    mEarth.Update(deltaTime, gRotateEarth);
    mMars.Update(deltaTime, gRotateMars);
    mJupiter.Update(deltaTime, gRotateJupiter);
    mSaturn.Update(deltaTime, gRotateSaturn);
    mUranus.Update(deltaTime, gRotateUranus);
    mNeptune.Update(deltaTime, gRotateNeptune);

    switch (mTarget)
    {
    case Sun:
        mRenderTargetCamera.SetPosition(mSun.GetPosition() + offset);
        mRenderTargetCamera.SetLookAt(mSun.GetPosition());
        break;
    case Mercury:
        mRenderTargetCamera.SetPosition(mMercury.GetPosition() + offset);
        mRenderTargetCamera.SetLookAt(mMercury.GetPosition());
        break;
    case Venus:
        mRenderTargetCamera.SetPosition(mVenus.GetPosition() + offset);
        mRenderTargetCamera.SetLookAt(mVenus.GetPosition());
        break;
    case Earth:
        mRenderTargetCamera.SetPosition(mEarth.GetPosition() + offset);
        mRenderTargetCamera.SetLookAt(mEarth.GetPosition());
        break;
    case Mars:
        mRenderTargetCamera.SetPosition(mMars.GetPosition() + offset);
        mRenderTargetCamera.SetLookAt(mMars.GetPosition());
        break;
    case Jupiter:
        mRenderTargetCamera.SetPosition(mJupiter.GetPosition() + offset);
        mRenderTargetCamera.SetLookAt(mJupiter.GetPosition());
        break;
    case Saturn:
        mRenderTargetCamera.SetPosition(mSaturn.GetPosition() + offset);
        mRenderTargetCamera.SetLookAt(mSaturn.GetPosition());
        break;
    case Uranus:
        mRenderTargetCamera.SetPosition(mUranus.GetPosition() + offset);
        mRenderTargetCamera.SetLookAt(mUranus.GetPosition());
        break;
    case Neptune:
        mRenderTargetCamera.SetPosition(mNeptune.GetPosition() + offset);
        mRenderTargetCamera.SetLookAt(mNeptune.GetPosition());
        break;
    }

}
void GameState::DebugUI()
{
    ImGui::Begin("Debug Draw", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Checkbox("Draw World", &mDrawWorld);
    if (mDrawWorld)
    {}
    ImGui::Checkbox("Draw Sun", &mDrawSphereSun);
    if (mDrawSphereSun)
    {}
    ImGui::Checkbox("Draw Mercury", &mDrawSphereMercury);
    if (mDrawSphereMercury)
    {
        ImGui::DragFloat("Rotate Mercury Speed##", &gRotateMercury,0.1f, 0.0f, 1.0f);
        ImGui::Checkbox("Draw Mercury Circle", &mCircleSphereMercury);
        if (mCircleSphereMercury)
        {
            SimpleDraw::AddCircle(360, 20, Colors::Brown);
        }

    }
    ImGui::Checkbox("Draw Venus", &mDrawSphereVenus);
    if (mDrawSphereVenus)
    {
        ImGui::DragFloat("Rotate Venus Speed##", &gRotateVenus, 0.1f, 0.0f, 1.0f);
        ImGui::Checkbox("Draw Venus Circle", &mCircleSphereVenus);
        if (mCircleSphereVenus)
        {
            SimpleDraw::AddCircle(360, 40, Colors::Yellow);
        }
    }
    ImGui::Checkbox("Draw Earth ", &mDrawSphereEarth);
    if (mDrawSphereEarth)
    {
        ImGui::DragFloat("Rotate Earth Speed##", &gRotateEarth, 0.1f, 0.0f, 1.0f);
        ImGui::Checkbox("Draw Earth Circle", &mCircleSphereEarth);
        if (mCircleSphereEarth)
        {
            SimpleDraw::AddCircle(360, 60, Colors::AliceBlue);
        }
    }
    ImGui::Checkbox("Draw Mars", &mDrawSphereMars);
    if (mDrawSphereMars)
    {
        ImGui::DragFloat("Rotate Mars Speed##", &gRotateMars, 0.1f, 0.0f, 1.0f);
        ImGui::Checkbox("Draw Mars Circle", &mCircleSphereMars);
        if (mCircleSphereMars)
        {
            SimpleDraw::AddCircle(360, 80, Colors::IndianRed);
        }
    }
    ImGui::Checkbox("Draw Jupiter", &mDrawSphereJupiter);
    if (mDrawSphereJupiter)
    {
        ImGui::DragFloat("Rotate Jupiter Speed##", &gRotateJupiter, 0.1f, 0.0f, 1.0f);
        ImGui::Checkbox("Draw Jupiter Circle", &mCircleSphereJupiter);
        if (mCircleSphereJupiter)
        {
            SimpleDraw::AddCircle(360, 100, Colors::AntiqueWhite);
        }
    }
    ImGui::Checkbox("Draw Saturn", &mDrawSphereSaturn);
    if (mDrawSphereSaturn)
    {
        ImGui::DragFloat("Rotate Saturn Speed##", &gRotateSaturn, 0.1f, 0.0f, 1.0f);
        ImGui::Checkbox("Draw Saturn Circle", &mCircleSphereSaturn);
        if (mCircleSphereSaturn)
        {
            SimpleDraw::AddCircle(360, 120, Colors::LawnGreen);
        }
    }
    ImGui::Checkbox("Draw Uranus", &mDrawSphereUranus);
    if (mDrawSphereUranus)
    {
        ImGui::DragFloat("Rotate Uranus Speed##", &gRotateUranus, 0.1f, 0.0f, 1.0f);
        ImGui::Checkbox("Draw Uranus Circle", &mCircleSphereUranus);
        if (mCircleSphereUranus)
        {
            SimpleDraw::AddCircle(360, 140, Colors::LightSkyBlue);
        }
    }
    ImGui::Checkbox("Draw Neptune", &mDrawSphereNeptune);
    if (mDrawSphereNeptune)
    {
        ImGui::DragFloat("Rotate Neptune Speed##", &gRotateNeptune, 0.1f, 0.0f, 1.0f);
        ImGui::Checkbox("Draw Neptune Circle", &mCircleSphereNeptune);
        if (mCircleSphereNeptune)
        {
            SimpleDraw::AddCircle(360, 160, Colors::DarkBlue);
        }
    }

    SimpleDraw::Render(mCamera);

    
    ImGui::Text("Render Target");
    const char* targets[] = {
        "Sun",
        "Mercury",
        "Venus",
        "Earth",
        "Mars",
        "Jupiter",
        "Saturn",
        "Uranus", 
        "Neptune"
    };

    int currentItem = (int)mTarget;
    if (ImGui::Combo("Target", &currentItem, targets, static_cast<int>(std::size(targets))))
    {
        mTarget = (Planets)currentItem;
    }
    ImGui::Image(
    mRenderTarget.GetRawData(),
        {128, 128},
        {0 , 0},
        {1 , 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}
    );
    ImGui::End();
}

