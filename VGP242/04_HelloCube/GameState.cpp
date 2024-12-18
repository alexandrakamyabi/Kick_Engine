#include "GameState.h"

using namespace Kick_Engine::Graphics;
using namespace Kick_Engine;
using namespace Kick_Engine::Input;

void GameState::Initialize()
{

    CreateShape();
    mCamera.SetPosition({ 0.0f, 1.0f, -2.5f });
    mCamera.SetLookAt({0.0f, 0.0f, 0.0f});

    mConstantBuffer.Initialize(sizeof(Matrix4));

    MeshPC cube = MeshBuilder::CreateCubePC(1.0f, Colors::Wheat);
    mMeshBuffer.Initialize(cube);
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
    //Vertices[]
    // indices[] indexes of vertices
    // Vertex position, color, uv
    // float3, float4, float2 = 9floats * 4bytes = 36 bytes per vertex
    // int = 4bytes
    // 
    //FRONT
    mVerticies.push_back({ Vector3(-0.5f, -0.5f, -0.5f), Colors::Cyan });
    mVerticies.push_back({ Vector3(-0.5f, 0.5f, -0.5f), Colors::Blue });
    mVerticies.push_back({ Vector3(0.5f, -0.5f, -0.5f), Colors::Teal });

    mVerticies.push_back({ Vector3(0.5f, -0.5f, -0.5f), Colors::Teal });
    mVerticies.push_back({ Vector3(-0.5f, 0.5f, -0.5f), Colors::Cyan });
    mVerticies.push_back({ Vector3(0.5f, 0.5f, -0.5f), Colors::Blue });

    //BACK
    mVerticies.push_back({ Vector3(-0.5f, -0.5f, 0.5f), Colors::Cyan });
    mVerticies.push_back({ Vector3(-0.5f, 0.5f, 0.5f), Colors::Blue });
    mVerticies.push_back({ Vector3(0.5f, -0.5f, 0.5f), Colors::Teal });

    mVerticies.push_back({ Vector3(0.5f, -0.5f, 0.5f), Colors::Teal });
    mVerticies.push_back({ Vector3(-0.5f, 0.5f, 0.5f), Colors::Cyan });
    mVerticies.push_back({ Vector3(0.5f, 0.5f, 0.5f), Colors::Blue });

    //RIGHT
    mVerticies.push_back({ Vector3(0.5f, -0.5f, -0.5f), Colors::Cyan });
    mVerticies.push_back({ Vector3(0.5f, 0.5f, -0.5f), Colors::Blue });
    mVerticies.push_back({ Vector3(0.5f, -0.5f, 0.5f), Colors::Teal });

    mVerticies.push_back({ Vector3(0.5f, -0.5f, 0.5f), Colors::Teal });
    mVerticies.push_back({ Vector3(0.5f, 0.5f, -0.5f), Colors::Cyan });
    mVerticies.push_back({ Vector3(0.5f, 0.5f, 0.5f), Colors::Blue });

    //LEFT
    mVerticies.push_back({ Vector3(-0.5f, -0.5f, -0.5f), Colors::Cyan });
    mVerticies.push_back({ Vector3(-0.5f, 0.5f, -0.5f), Colors::Blue });
    mVerticies.push_back({ Vector3(-0.5f, -0.5f, 0.5f), Colors::Teal });

    mVerticies.push_back({ Vector3(-0.5f, -0.5f, 0.5f), Colors::Teal });
    mVerticies.push_back({ Vector3(-0.5f, 0.5f, -0.5f), Colors::Cyan });
    mVerticies.push_back({ Vector3(-0.5f, 0.5f, 0.5f), Colors::Blue });

    //TOP
    mVerticies.push_back({ Vector3(-0.5f, 0.5f, -0.5f), Colors::Cyan });
    mVerticies.push_back({ Vector3(-0.5f, 0.5f, 0.5f), Colors::Blue });
    mVerticies.push_back({ Vector3(0.5f, 0.5f, -0.5f), Colors::Teal });

    mVerticies.push_back({ Vector3(0.5f, 0.5f, -0.5f), Colors::Teal });
    mVerticies.push_back({ Vector3(-0.5f, 0.5f, 0.5f), Colors::Cyan });
    mVerticies.push_back({ Vector3(0.5f, 0.5f, 0.5f), Colors::Blue });

    //BOTTOM
    mVerticies.push_back({ Vector3(-0.5f, -0.5f, -0.5f), Colors::Cyan });
    mVerticies.push_back({ Vector3(0.5f, -0.5f, -0.5f), Colors::Blue });
    mVerticies.push_back({ Vector3(-0.5f, -0.5f, 0.5f), Colors::Teal });

    mVerticies.push_back({ Vector3(0.5f, 0.5f, -0.5f), Colors::Teal });
    mVerticies.push_back({ Vector3(0.5f, -0.5f, 0.5f), Colors::Cyan });
    mVerticies.push_back({ Vector3(-0.5f, -0.5f, 0.5f), Colors::Blue });
}
void TriangleState::Update(float deltaTime)
{
    auto input = InputSystem::Get();
    if (input->IsKeyPressed(KeyCode::DOWN))
    {
        App& myApp = MainApp();
        myApp.ChangeState("SquareState");
    }
    if (input->IsKeyPressed(KeyCode::NUMPAD1))
    {
        App& myApp = MainApp();
        myApp.ChangeState("ArrowState");
    }
    if (input->IsKeyPressed(KeyCode::NUMPAD2))
    {
        App& myApp = MainApp();
        myApp.ChangeState("HeartState");
    }
    if (input->IsKeyPressed(KeyCode::NUMPAD3))
    {
        App& myApp = MainApp();
        myApp.ChangeState("ZeldaState");
    }

    gRotationY += Constants::HalfPi * deltaTime * 0.25f;
    gRotationX += Constants::HalfPi * deltaTime * 0.25f;
}

void SquareState::CreateShape()
{
    mVerticies.push_back({ Vector3(-0.25f, 0.0f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(-0.25f, 0.5f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(0.25f, 0.5f, 0.0f), Colors::Purple });

    mVerticies.push_back({ Vector3(-0.25f, 0.0f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(0.25f, 0.5f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(0.25f, 0.0f, 0.0f), Colors::Green });
    mVerticies.push_back({ Vector3(0.30f, 0.0f, 0.0f), Colors::Green });
}
void SquareState::Update(float deltaTime)
{
    auto input = InputSystem::Get();
    if (input->IsKeyPressed(KeyCode::UP))
    {
        App& myApp = MainApp();
        myApp.ChangeState("TriangleState");
    }
    if (input->IsKeyPressed(KeyCode::NUMPAD1))
    {
        App& myApp = MainApp();
        myApp.ChangeState("ArrowState");
    }
    if (input->IsKeyPressed(KeyCode::NUMPAD2))
    {
        App& myApp = MainApp();
        myApp.ChangeState("HeartState");
    }
    if (input->IsKeyPressed(KeyCode::NUMPAD3))
    {
        App& myApp = MainApp();
        myApp.ChangeState("ZeldaState");
    }

    gRotationY += Constants::HalfPi * deltaTime * 1.5f;
    gRotationX += Constants::HalfPi * deltaTime * 0.5f;
}

// SHAPE 1 - DONE
void ArrowState::CreateShape()
{
    mVerticies.push_back({ Vector3(-0.25f, 0.5f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(0.0f, 0.75f, 0.0f), Colors::Green });
    mVerticies.push_back({ Vector3(0.25f, 0.5f, 0.0f), Colors::Red });

    mVerticies.push_back({ Vector3(-0.1f, 0.0f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(-0.1f, 0.5f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(0.1f, 0.5f, 0.0f), Colors::Purple });

    mVerticies.push_back({ Vector3(-0.1f, 0.0f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(0.1f, 0.5f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(0.1f, 0.0f, 0.0f), Colors::Green });



}
void ArrowState::Update(float deltaTime)
{
    auto input = InputSystem::Get();
    if (input->IsKeyPressed(KeyCode::UP))
    {
        App& myApp = MainApp();
        myApp.ChangeState("TriangleState");
    }
    if (input->IsKeyPressed(KeyCode::DOWN))
    {
        App& myApp = MainApp();
        myApp.ChangeState("SquareState");
    }
    if (input->IsKeyPressed(KeyCode::NUMPAD1))
    {
        App& myApp = MainApp();
        myApp.ChangeState("ArrowState");
    }
    if (input->IsKeyPressed(KeyCode::NUMPAD3))
    {
        App& myApp = MainApp();
        myApp.ChangeState("ZeldaState");
    }

}
// SHAPE 2 - DONE 
void HeartState::CreateShape()
{

    mVerticies.push_back({ Vector3(-0.4f, -0.10f, 0.0f), Colors::Red });    //done
    mVerticies.push_back({ Vector3(-0.2f, 0.40f, 0.0f), Colors::Green });
    mVerticies.push_back({ Vector3(0.0f, -0.10f, 0.0f), Colors::Red });

    mVerticies.push_back({ Vector3(0.0f, -0.10f, 0.0f), Colors::Red });        //done
    mVerticies.push_back({ Vector3(0.2f, 0.40f, 0.0f), Colors::Green });
    mVerticies.push_back({ Vector3(0.4f, -0.10f, 0.0f), Colors::Red });

    mVerticies.push_back({ Vector3(-0.4f, -0.10f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(0.4f, -0.10f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(0.0f, -0.80f, 0.0f), Colors::Green });

}
void HeartState::Update(float deltaTime)
{
    auto input = InputSystem::Get();
    if (input->IsKeyPressed(KeyCode::UP))
    {
        App& myApp = MainApp();
        myApp.ChangeState("TriangleState");
    }
    if (input->IsKeyPressed(KeyCode::DOWN))
    {
        App& myApp = MainApp();
        myApp.ChangeState("SquareState");
    }
    if (input->IsKeyPressed(KeyCode::NUMPAD2))
    {
        App& myApp = MainApp();
        myApp.ChangeState("HeartState");
    }
    if (input->IsKeyPressed(KeyCode::NUMPAD3))
    {
        App& myApp = MainApp();
        myApp.ChangeState("ZeldaState");
    }

}
// SHAPE 3 - DONE
void ZeldaState::CreateShape()
{
    mVerticies.push_back({ Vector3(-0.2f, 0.40f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(0.0f, 0.75f, 0.0f), Colors::Green });
    mVerticies.push_back({ Vector3(0.2f, 0.40f, 0.0f), Colors::Red });

    mVerticies.push_back({ Vector3(-0.4f, -0.10f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(-0.2f, 0.40f, 0.0f), Colors::Green });
    mVerticies.push_back({ Vector3(0.0f, -0.10f, 0.0f), Colors::Red });

    mVerticies.push_back({ Vector3(0.0f, -0.10f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(0.2f, 0.40f, 0.0f), Colors::Green });
    mVerticies.push_back({ Vector3(0.4f, -0.10f, 0.0f), Colors::Red });
}
void ZeldaState::Update(float deltaTime)
{
    auto input = InputSystem::Get();

    if (input->IsKeyPressed(KeyCode::UP))
    {
        App& myApp = MainApp();
        myApp.ChangeState("TriangleState");
    }
    if (input->IsKeyPressed(KeyCode::DOWN))
    {
        App& myApp = MainApp();
        myApp.ChangeState("SquareState");
    }
    if (input->IsKeyPressed(KeyCode::NUMPAD1))
    {
        App& myApp = MainApp();
        myApp.ChangeState("ArrowState");
    }
    if (input->IsKeyPressed(KeyCode::NUMPAD2))
    {
        App& myApp = MainApp();
        myApp.ChangeState("HeartState");
    }

}

