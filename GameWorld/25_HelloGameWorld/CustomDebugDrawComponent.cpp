#include "CustomDebugDrawComponent.h"

#include "CustomDebugDrawDisplayService.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Kick_Math;

void CustomDebugDrawComponent::Initialize()
{
    mTransformComponent = GetOwner().GetComponent<TransformComponent>();
    CustomDebugDrawDisplayService* displayService = GetOwner().GetWorld().GetService<CustomDebugDrawDisplayService>();
    displayService->Register(this);

    UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
    updateService->Register(this);
}

void CustomDebugDrawComponent::Terminate()
{
    CustomDebugDrawDisplayService* displayService = GetOwner().GetWorld().GetService<CustomDebugDrawDisplayService>();
    displayService->Unregister(this);
}

void CustomDebugDrawComponent::Update(float deltaTime)
{
    SoundBankComponent* soundBank = GetOwner().GetComponent<SoundBankComponent>();
    RigidBodyComponent* rigidBody = GetOwner().GetComponent<RigidBodyComponent>();

}

void CustomDebugDrawComponent::AddDebugDraw()
{
    Vector3 worldSpace = mPosition;
    if (mTransformComponent != nullptr)
    {
        Matrix4 matWorld = mTransformComponent->GetMatrix4();
        worldSpace = TransformCoord(mPosition, matWorld);
    }
    SimpleDraw::AddSphere(mSlices, mRings, mRadius, worldSpace, mColor);
}

void CustomDebugDrawComponent::Deserialize(const rapidjson::Value& value)
{
    if (value.HasMember("Slices"))
    {
        mSlices = static_cast<uint32_t>(value["Slices"].GetInt());
    }
    if (value.HasMember("Rings"))
    {
        mRings = static_cast<uint32_t>(value["Rings"].GetInt());
    }
    if (value.HasMember("Radius"))
    {
        mRadius = value["Radius"].GetFloat();
    }
    if (value.HasMember("Position"))
    {
        auto pos = value["Position"].GetArray();
        mPosition.x = pos[0].GetFloat();
        mPosition.y = pos[1].GetFloat();
        mPosition.z = pos[2].GetFloat();
    }
    if (value.HasMember("Color"))
    {
        auto color = value["Color"].GetArray();
        mColor.r = color[0].GetFloat();
        mColor.g = color[1].GetFloat();
        mColor.b = color[2].GetFloat();
        mColor.a = color[3].GetFloat();
    }

}
