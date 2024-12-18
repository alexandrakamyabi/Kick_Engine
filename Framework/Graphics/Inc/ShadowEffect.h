#pragma once

#include "Camera.h"
#include "ConstantBuffer.h"
#include "LightTypes.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "RenderTarget.h"

namespace Kick_Engine::Graphics
{
    class RenderObject;

    class ShadowEffect
    {
    public:
        void Initialize();
        void Terminate();

        void Begin();
        void End();

        void Render(const RenderObject& renderObject);

        void DebugUI();

        void SetDirectionalLight(const DirectionalLight& directionalLight);
        void SetFocus(const Kick_Math::Vector3& focusPosition);
        void SetSize(float size);
        const Camera& GetLightCamera() const;
        const Texture& GetDepthMap() const;
        void UpdateLightCamera();

    private:
        struct TransformData
        {
            Kick_Math::Matrix4 wvp;
        };

        using TransformBuffer = TypedConstantBuffer<TransformData>;
        TransformBuffer mTransformBuffer;

        VertexShader mVertexShader;
        PixelShader mPixelShader;

        Camera mLightCamera;
        RenderTarget mDepthMapRenderTarget;

        const DirectionalLight* mDirectionalLight = nullptr;


        Kick_Math::Vector3 mFocusPosition = Kick_Math::Vector3::Zero;
        float mSize = 100.0f;
    };
}
