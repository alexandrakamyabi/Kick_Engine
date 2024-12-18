#pragma once

#include "ConstantBuffer.h"
#include "LightTypes.h"
#include "Material.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"
#include "VertexTypes.h"

namespace Kick_Engine::Graphics
{
    class Camera;
    class Texture;
    class RenderObject;

    class TerrainEffect final
    {
    public:
        void Initialize();
        void Terminate();

        void Begin();
        void End();

        void Render(const RenderObject& renderObject);
        void DebugUI();

        void SetCamera(const Camera& camera);
        void SetLightCamera(const Camera& camera);
        void SetDirectionalLight(const DirectionalLight& directionalLight);
        void SetShadowMap(const Texture& shadowMap);
        void ChangeBlend();
        void NormalBlend();

    private:
        struct TransformData
        {
            Kick_Math::Matrix4 wvp;
            Kick_Math::Matrix4 lwvp;
            Kick_Math::Matrix4 world;
            Kick_Math::Vector3 viewPosition;
            float padding = 0.0f;
        };

        struct SettingsData
        {
            int useNormalMap = 0;
            int useSpecMap = 0;
            int useShadowMap = 0;
            int useBlend = 1;
            float depthBias = 0.0f;
            float blendHeight = 0.0f;
            float blendWidth = 0.0f;
            float padding[1];
        };

        using TransformBuffer = TypedConstantBuffer<TransformData>;
        using LightingBuffer = TypedConstantBuffer<DirectionalLight>;
        using MaterialBuffer = TypedConstantBuffer<Material>;
        using SettingsBuffer = TypedConstantBuffer<SettingsData>;

        TransformBuffer mTransformBuffer;
        LightingBuffer mLightingBuffer;
        MaterialBuffer mMaterialBuffer;
        SettingsBuffer mSettingsBuffer;

        VertexShader mVertexShader;
        PixelShader mPixelShader;
        Sampler mSampler;

        SettingsData mSettingsData;
        const Camera* mCamera = nullptr;
        const Camera* mLightCamera = nullptr;
        const DirectionalLight* mDirectionalLight = nullptr;
        const Texture* mShadowMap = nullptr;
    };
}