#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"
#include "BlendState.h"

namespace Kick_Engine::Graphics
{
    class Camera;
    class RenderObject;

    class BillboardEffect
    {
    public:
        void Initialize();
        void Terminate();

        void Begin();
        void End();
        void Render(const RenderObject& renderObject);
        void SetCamera(const Camera& camera);

    private:
        const Camera* mCamera = nullptr;

        ConstantBuffer mConstantBuffer;
        VertexShader mVertexShader;
        PixelShader mPixelShader;
        Sampler mSampler;
        BlendState mBlendState;
    };
}
