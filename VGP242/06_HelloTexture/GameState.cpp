#include "GameState.h"

using namespace Kick_Engine::Graphics;
using namespace Kick_Engine;
using namespace Kick_Engine::Input;

void GameState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 0.0f, -3.0f });
    mCamera.SetLookAt({0.0f, 0.0f, 0.0f});

    mConstantBuffer.Initialize(sizeof(Matrix4));

    MeshPX cube = MeshBuilder::CreateSkyboxPX(100.0f);
    MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 1.0f);
    //MeshPC rect = MeshBuilder::CreateRectPC(1.0f, 2.0f, 3.0f);
    //MeshPC plane = MeshBuilder::CreatePlanePC(3, 3, 2.0f);
    //MeshPC cylinder = MeshBuilder::CreateCylinderPC(8,2);
    mMeshBuffer.Initialize(cube);
    //mMeshBuffer.Initialize(mVerticies.data(), sizeof(Vertex), mVerticies.size());

    std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexturing.fx";
    mVertexShader.Initialize<VertexPX>(shaderFile);
    mPixelShader.Initialize(shaderFile);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/skybox/skybox_texture.jpg");
    mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

}
void GameState::Terminate()
{
    mVertexShader.Terminate();
    mMeshBuffer.Terminate();
    mMeshBuffer.Terminate();
    mConstantBuffer.Terminate();
}
float gRotationY = 0.0f;
float gRotationX = 0.0f;
void GameState::Render()
{
    mVertexShader.Bind();
    mPixelShader.Bind();
    mDiffuseTexture.BindPS(0);
    mSampler.BindPS(0);

    Matrix4 matWorld = Matrix4::RotationX(gRotationX) * Matrix4::RotationY(gRotationY);
    Matrix4 matView = mCamera.GetViewMatrix();
    Matrix4 matProj = mCamera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal);

    mConstantBuffer.Update(&wvp);
    mConstantBuffer.BindVS(0);

    mMeshBuffer.Render();


}
void GameState::Update(float deltaTime)
{
    auto input = InputSystem::Get();
    if (input->IsKeyDown(KeyCode::UP))
    {
        gRotationX += Constants::HalfPi * deltaTime * 0.5f;
    }
    else if (input->IsKeyDown(KeyCode::DOWN))
    {
        gRotationX -= Constants::HalfPi * deltaTime * 0.5f;
    }
    if (input->IsKeyDown(KeyCode::LEFT))
    {
        gRotationY -= Constants::HalfPi * deltaTime * 0.5f;
    }
    else if (input->IsKeyDown(KeyCode::RIGHT))
    {
        gRotationY += Constants::HalfPi * deltaTime * 0.5f;
    }

}

