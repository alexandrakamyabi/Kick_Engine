#include "GameState.h"

using namespace Kick_Engine::Graphics;
using namespace Kick_Engine;
using namespace Kick_Engine::Input;

void GameState::Initialize()
{
    // NDC - Normalized Device Coordinate
    // create shapes
    // in form of triangles

    CreateShape();

    auto device = GraphicsSystem::Get()->GetDevice();
    //===============================================================
    //Create a vertex buffer
    D3D11_BUFFER_DESC bufferDesc{};
    bufferDesc.ByteWidth = static_cast<UINT>(mVerticies.size() * sizeof(Vertex));
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;
    
    D3D11_SUBRESOURCE_DATA initData{};
    initData.pSysMem = mVerticies.data();

    HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &mVetexBuffer);
    ASSERT(SUCCEEDED(hr), "Failed to create vertex buffer");

    //===============================================================
    //Create a vertex shader
    std::filesystem::path shaderFile = L"../../Assets/Shaders/DoSomething.fx";

    DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
    ID3DBlob* shaderBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;
    hr = D3DCompileFromFile(
        shaderFile.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VS", "vs_5_0",
        shaderFlags, 0,
        &shaderBlob,
        &errorBlob
    );

    if (errorBlob && errorBlob->GetBufferPointer())
    {
        LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
    }

    ASSERT(SUCCEEDED(hr), "Failed to compile vertex shader");

    hr = device->CreateVertexShader(
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        nullptr,
        &mVertexShader);

    ASSERT(SUCCEEDED(hr), "Failed to create vertex shader");
    //===============================================================
    //Create a input layout
    std::vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout;
    vertexLayout.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });
    vertexLayout.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });

    hr = device->CreateInputLayout(
        vertexLayout.data(),
        (UINT)vertexLayout.size(),
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        &mInputLayout
    );
    ASSERT(SUCCEEDED(hr), "Failed to create input layout");
    SafeRelease(shaderBlob);
    SafeRelease(errorBlob);

    //===============================================================
    //Create a pixel shader

    hr = D3DCompileFromFile(
        shaderFile.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PS", "ps_5_0",
        shaderFlags, 0,
        &shaderBlob,
        &errorBlob
    );

    if (errorBlob && errorBlob->GetBufferPointer())
    {
        LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
    }

    ASSERT(SUCCEEDED(hr), "Failed to compile pixel shader");

    hr = device->CreatePixelShader(
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        nullptr,
        &mPixelShader);
    ASSERT(SUCCEEDED(hr), "Failed to create input layout");
    SafeRelease(shaderBlob);
    SafeRelease(errorBlob);
}
void GameState::Terminate()
{
    mVerticies.clear();
    SafeRelease(mVetexBuffer);
    SafeRelease(mVertexShader);
    SafeRelease(mPixelShader);
    SafeRelease(mInputLayout);
}
void GameState::Render()
{
    auto context = GraphicsSystem::Get()->GetContext();

    context->VSSetShader(mVertexShader, nullptr, 0);
    context->IASetInputLayout(mInputLayout);
    context->PSSetShader(mPixelShader, nullptr, 0);


    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, &mVetexBuffer, &stride, &offset);
    context->Draw((UINT)mVerticies.size(), 0);

}

void TriangleState::CreateShape()
{
    mVerticies.push_back({ Vector3(-0.5f, 0.0f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(0.0f, 0.75f, 0.0f), Colors::Purple });
    mVerticies.push_back({ Vector3(0.5f, 0.0f, 0.0f), Colors::Red });
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
}

void SquareState::CreateShape()
{
    mVerticies.push_back({ Vector3(-0.25f, 0.0f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(-0.25f, 0.5f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(0.25f, 0.5f, 0.0f), Colors::Purple });

    mVerticies.push_back({ Vector3(-0.25f, 0.0f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(0.25f, 0.5f, 0.0f), Colors::Red });
    mVerticies.push_back({ Vector3(0.25f, 0.0f, 0.0f), Colors::Green });
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
