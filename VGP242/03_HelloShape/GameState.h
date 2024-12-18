#pragma once

#include "Inc/AppState.h"
#include "Inc/Kick_Engine.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Kick_Math;

class GameState : public AppState
{
public:
    void Initialize();
    void Terminate();
    void Render();
protected:
    virtual void CreateShape() = 0;



protected:
    struct Vertex
    {
        Vector3 position;
        Color color;
    };

    using Verticies = std::vector<Vertex>;
    Verticies mVerticies;

    ID3D11Buffer* mVetexBuffer = nullptr;
    ID3D11VertexShader* mVertexShader = nullptr;
    ID3D11InputLayout* mInputLayout = nullptr;
    ID3D11PixelShader* mPixelShader = nullptr;

};

class TriangleState : public GameState
{
public:
    void CreateShape();
    void Update(float deltaTime);
};

class SquareState : public GameState
{
public:
    void CreateShape();
    void Update(float deltaTime);
};

class HeartState : public GameState
{
public:
    void CreateShape();
    void Update(float deltaTime);
};

class ArrowState : public GameState
{
public:
    void CreateShape();
    void Update(float deltaTime);
};

class ZeldaState : public GameState
{
public:
    void CreateShape();
    void Update(float deltaTime);
};