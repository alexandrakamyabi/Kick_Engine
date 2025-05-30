#include "Precompiled.h"
#include "ShadowEffect.h"

#include "RenderObject.h"
#include "VertexTypes.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;

void ShadowEffect::Initialize()
{
    std::filesystem::path shaderFile = L"../../Assets/Shaders/Shadow.fx";
    mVertexShader.Initialize<Vertex>(shaderFile);
    mPixelShader.Initialize(shaderFile);

    mTransformBuffer.Initialize();

    mLightCamera.SetMode(Camera::ProjectionMode::Orthographic);
    mLightCamera.SetNearPlane(1.0f);
    mLightCamera.SetFarPlane(2000.0f);

    constexpr uint32_t depthMapResolution = 4096;
    mDepthMapRenderTarget.Initialize(depthMapResolution, depthMapResolution, Texture::Format::RGBA_U32);
}

void ShadowEffect::Terminate()
{
    mDepthMapRenderTarget.Terminate();
    mTransformBuffer.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();
}

void ShadowEffect::Begin()
{
    UpdateLightCamera();

    mVertexShader.Bind();
    mPixelShader.Bind();
    mTransformBuffer.BindVS(0);

    mDepthMapRenderTarget.BeginRender();
}

void ShadowEffect::End()
{
    mDepthMapRenderTarget.EndRender();
}

void ShadowEffect::Render(const RenderObject& renderObject)
{
    const Kick_Math::Matrix4 matWorld = renderObject.transform.GetMatrix4();
    const Kick_Math::Matrix4 matView = mLightCamera.GetViewMatrix();
    const Kick_Math::Matrix4 matProj = mLightCamera.GetProjectionMatrix();

    TransformData data;
    data.wvp = Kick_Math::Transpose(matWorld * matView * matProj);
    mTransformBuffer.Update(data);

    renderObject.meshBuffer.Render();
}

void ShadowEffect::DebugUI()
{
    if (ImGui::CollapsingHeader("ShadowEffect", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("DepthMap");
        ImGui::Image(
            mDepthMapRenderTarget.GetRawData(),
            {144,144},
            {0, 0},
            {1, 1},
            {1, 1, 1, 1},
            {1, 1, 1, 1});
        ImGui::DragFloat("Size##Shadow", &mSize, 1.0f, 1.0f, 1000.0f);
    }
}

void ShadowEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
    mDirectionalLight = &directionalLight;
}

void ShadowEffect::SetFocus(const Kick_Math::Vector3& focusPosition)
{
    mFocusPosition = focusPosition;
}

void ShadowEffect::SetSize(float size)
{
    mSize = size;
}

const Camera& ShadowEffect::GetLightCamera() const
{
    return mLightCamera;
}

const Texture& ShadowEffect::GetDepthMap() const
{
    return mDepthMapRenderTarget;
}

void ShadowEffect::UpdateLightCamera()
{
    ASSERT(mDirectionalLight != nullptr, "ShadowEffect: no light set");
    const Kick_Math::Vector3& direction = mDirectionalLight->direction;
    mLightCamera.SetDirection(direction);
    mLightCamera.SetPosition(mFocusPosition - (direction * 1000.0f));
    mLightCamera.SetSize(mSize, mSize);
}
