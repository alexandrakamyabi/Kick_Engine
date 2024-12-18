#pragma once

#include "Inc/AppState.h"
#include "Inc/Kick_Engine.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Kick_Math;
using namespace Kick_Engine::Graphics;

class GameState : public AppState
{
public:
    void Initialize();
    void Terminate();
    void Render();
    void Update(float deltaTime);
protected:
    Camera mCamera;
    ConstantBuffer mConstantBuffer;
    MeshBuffer mMeshBuffer ;
    VertexShader mVertexShader;
    PixelShader mPixelShader;

    Texture mDiffuseTexture;
    Sampler mSampler;
};

