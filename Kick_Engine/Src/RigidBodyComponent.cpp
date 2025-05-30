#include "Precompiled.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"

#include "PhysicsService.h"
#include "GameWorld.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Physics;

void RigidBodyComponent::Initialize()
{
    PhysicsService* physicsService = GetOwner().GetWorld().GetService<PhysicsService>();
    if (physicsService != nullptr)
    {
        TransformComponent* transformComponent = GetOwner().GetComponent<TransformComponent>();
        mRigidBody.Initialize(*transformComponent, mCollisionShape, mMass);
        physicsService->Register(this);
    }
}

void RigidBodyComponent::Terminate()
{
    PhysicsService* physicsService = GetOwner().GetWorld().GetService<PhysicsService>();
    if (physicsService != nullptr)
    {
        physicsService->Unregister(this);
    }
    mRigidBody.Terminate();
    mCollisionShape.Terminate();
}

void RigidBodyComponent::Deserialize(const rapidjson::Value& value)
{
    if (value.HasMember("Mass"))
    {
        mMass = value["Mass"].GetFloat();
    }
    if (value.HasMember("ColliderData"))
    {
        auto colliderData = value["ColliderData"].GetObj();
        if (colliderData.HasMember("Shape"))
        {
            std::string shape = colliderData["Shape"].GetString();
            if (shape == "Empty")
            {
                mCollisionShape.InitializeEmpty();
            }
            else if (shape == "Box")
            {
                const auto halfExtents = colliderData["HalfExtents"].GetArray();
                const float x = halfExtents[0].GetFloat();
                const float y = halfExtents[1].GetFloat();
                const float z = halfExtents[2].GetFloat();
                mCollisionShape.InitializeBox({ x, y, z });
            }
            else if (shape == "Sphere")
            {
                const float radius = colliderData["Radius"].GetFloat();
                mCollisionShape.InitializeSphere(radius);
            }
            else if (shape == "Hull")
            {
                const auto halfExtents = colliderData["HalfExtents"].GetArray();
                const float heX = halfExtents[0].GetFloat();
                const float heY = halfExtents[1].GetFloat();
                const float heZ = halfExtents[2].GetFloat();
                const auto origin = colliderData["Origin"].GetArray();
                const float oX = origin[0].GetFloat();
                const float oY = origin[1].GetFloat();
                const float oZ = origin[2].GetFloat();
                mCollisionShape.InitializeHull({ heX, heY, heZ }, { oX, oY, oZ });
            }
            else
            {
                ASSERT(false, "RigidBodyComponent: Invalid shape type %s", shape.c_str());
            }
        }
        else
        {
            ASSERT(false, "RigidBodyComponent: collision must have valid shape data");
        }
    }
    else
    {
        ASSERT(false, "RigidBodyComponent: must have ColliderData");
    }
}

void RigidBodyComponent::SetPosition(const Kick_Math::Vector3& position)
{
    mRigidBody.SetPosition(position);
}

void RigidBodyComponent::SetVelocity(const Kick_Math::Vector3& velocity)
{
    mRigidBody.SetVelocity(velocity);
}
void RigidBodyComponent::SetRotationVelocity(const Kick_Engine::Kick_Math::Vector3& velocity)
{
    mRigidBody.SetRotationVelocity(velocity);
}
Vector3 RigidBodyComponent::GetVelocity()
{
    return mRigidBody.GetVelocity();
}

Vector3 RigidBodyComponent::GetPosition()
{
    return mRigidBody.GetPosition();
}
