#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "Material.h"
#include "VertexShader.h"
#include "LightTypes.h"

namespace Kick_Engine::Graphics
{
    class Camera;
    class RenderObject;
    class Texture;

    class StandardEffect
    {
    public:
        void Initialize(const std::filesystem::path& filePath);
        void Terminate();

        void Begin();
        void End();

        void Render(const RenderObject& renderObject);

        void SetCamera(const Camera& camera);
        void SetLightCamera(const Camera& camera);
        void SetDirectionalLight(const DirectionalLight& directionalLight);
        void SetShadowMap(const Texture& shadowMap);

        void DebugUI();
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
            int useDiffuseMap = 1;
            int useNormalMap = 1;
            int useSpecMap = 1;
            int useBumpMap = 1;
            int useShadowMap = 1;
            int useSkinning = 1;
            float bumpWeight = 1.0f;
            float depthBias = 0.0003f;
        };

        using TransformBuffer = TypedConstantBuffer<TransformData>;
        using LightBuffer = TypedConstantBuffer<DirectionalLight>;
        using MaterialBuffer = TypedConstantBuffer<Material>;
        using SettingsBuffer = TypedConstantBuffer<SettingsData>;
        using BoneTransformBuffer = ConstantBuffer;

        TransformBuffer mTransformBuffer;
        LightBuffer mLightBuffer;
        MaterialBuffer mMaterialBuffer;
        SettingsBuffer mSettingsBuffer;
        BoneTransformBuffer mBoneTransformBuffer;
        Sampler mSampler;
        VertexShader mVertexShader;
        PixelShader mPixelShader;
        

        SettingsData mSettingsData;
        const Camera* mCamera = nullptr;
        const Camera* mLightCamera = nullptr;
        const DirectionalLight* mDirectionalLight = nullptr;
        const Texture* mShadowMap = nullptr;
    };
}