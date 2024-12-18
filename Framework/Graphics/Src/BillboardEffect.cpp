#include "Precompiled.h"
#include "BillboardEffect.h"

#include "Camera.h"
#include "GraphicsSystem.h"
#include "RenderObject.h"
#include "TextureManager.h"
#include "VertexTypes.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;

void BillboardEffect::Initialize()
{
    std::filesystem::path filePath = L"../../Assets/Shaders/Billboard.fx";
    mVertexShader.Initialize<Vertex>(filePath);
    mPixelShader.Initialize(filePath);
    mConstantBuffer.Initialize(sizeof(Kick_Math::Matrix4));
    mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
    mBlendState.Initialize(BlendState::Mode::AlphaBlend);

}

void BillboardEffect::Terminate()
{
    mSampler.Terminate();
    mConstantBuffer.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();
    mBlendState.Terminate();
}

void BillboardEffect::Begin()
{
    mVertexShader.Bind();
    mPixelShader.Bind();
    mConstantBuffer.BindVS(0);
    mSampler.BindPS(0);
    mBlendState.Set();
}

void BillboardEffect::End()
{
    Texture::UnbindPS(0);
    BlendState::ClearState();
}

void BillboardEffect::Render(const RenderObject& renderObject)
{
    Kick_Math::Matrix4 matView = mCamera->GetViewMatrix();
    Kick_Math::Matrix4 matWV = Kick_Math::Matrix4::Translation(Kick_Math::TransformCoord(renderObject.transform.position, matView));
    Kick_Math::Matrix4 matProj = mCamera->GetProjectionMatrix();
    Kick_Math::Matrix4 matFinal = matWV * matProj;
    Kick_Math::Matrix4 wvp = Kick_Math::Transpose(matFinal);

    mConstantBuffer.Update(&wvp);
    TextureManager* tm = TextureManager::Get();
    tm->BindPS(renderObject.diffuseMapId, 0);
    renderObject.meshBuffer.Render();
}

void BillboardEffect::SetCamera(const Camera& camera)
{
    mCamera = &camera;
}
