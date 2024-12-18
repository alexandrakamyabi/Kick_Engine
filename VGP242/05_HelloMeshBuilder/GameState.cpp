#include "GameState.h"

using namespace Kick_Engine::Graphics;
using namespace Kick_Engine;
using namespace Kick_Engine::Input;

void GameState::Initialize()
{

    CreateShape();
    //mCamera.SetPosition({ 0.0f, 1.0f, -2.5f });
    mCamera.SetPosition({ 0.0f, 0.0f, -10.0f });
    mCamera.SetLookAt({0.0f, 0.0f, 0.0f});

    mConstantBuffer.Initialize(sizeof(Matrix4));

    MeshPC cube = MeshBuilder::CreateCubePC(1.0f, Colors::Wheat);
    MeshPC rect = MeshBuilder::CreateRectPC(1.0f, 2.0f, 3.0f);
    MeshPC plane = MeshBuilder::CreatePlanePC(3, 3, 2.0f);
    MeshPC cylinder = MeshBuilder::CreateCylinderPC(8,2);
    MeshPC sphere = MeshBuilder::CreateSpherePC(30, 30, 1.0f);
    mMeshBuffer.Initialize(shape);
    //mMeshBuffer.Initialize(mVerticies.data(), sizeof(Vertex), mVerticies.size());

    std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTransform.fx";
    mVertexShader.Initialize(shaderFile, VE_Position | VE_Color);
    mPixelShader.Initialize(shaderFile);
    
}
void GameState::Terminate()
{
    mVerticies.clear();
    mVertexShader.Terminate();
    mMeshBuffer.Terminate();
    mMeshBuffer.Terminate();

}
float gRotationY = 0.0f;
float gRotationX = 0.0f;
void GameState::Render()
{
    mVertexShader.Bind();
    mPixelShader.Bind();

    Matrix4 matWorld = Matrix4::RotationY(gRotationY) * Matrix4::RotationX(gRotationX);
    Matrix4 matView = mCamera.GetViewMatrix();
    Matrix4 matProj = mCamera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal);

    mConstantBuffer.Update(&wvp);
    mConstantBuffer.BindVS(0);

    mMeshBuffer.Render();


}

void TriangleState::CreateShape()
{

}
void TriangleState::Update(float deltaTime)
{
    auto input = InputSystem::Get();
    if (input->IsKeyPressed(KeyCode::F1))
    {
        shape = MeshBuilder::CreateCubePC(1.0f, Colors::Wheat);
        mMeshBuffer.Initialize(shape);
    }
    if (input->IsKeyPressed(KeyCode::F2))
    {
        shape = MeshBuilder::CreateRectPC(1.0f, 2.0f, 3.0f);
        mMeshBuffer.Initialize(shape);
    }
    if (input->IsKeyPressed(KeyCode::F3))
    {
        shape = MeshBuilder::CreatePlanePC(3, 3, 2.0f);
        mMeshBuffer.Initialize(shape);
    }
    if (input->IsKeyPressed(KeyCode::F4))
    {
        shape = MeshBuilder::CreateCylinderPC(8, 2);
        mMeshBuffer.Initialize(shape);
    }
    if (input->IsKeyPressed(KeyCode::F5))
    {
        shape = MeshBuilder::CreateSpherePC(30, 30, 1.0f);
        mMeshBuffer.Initialize(shape);
    }

    gRotationY += Constants::HalfPi * deltaTime * 0.25f;
    gRotationX += Constants::HalfPi * deltaTime * 0.25f;
}

