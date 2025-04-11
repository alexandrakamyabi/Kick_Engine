#pragma once

#include <../Kick_Engine/Inc/Kick_Engine.h>
#include "TypeIds.h"

namespace Kick_Engine
{
    class CameraComponent;

    class TPSCameraComponent final : public Kick_Engine::Component
    {
    public:
        SET_TYPE_ID(ComponentId::TPSCamera);

        void Initialize() override;
        void Deserialize(const rapidjson::Value& value) override;
        void Terminate() override;
        void Update(float deltaTime) override;

    private:
        Kick_Engine::CameraComponent* mCameraComponent = nullptr;
        Kick_Engine::RigidBodyComponent* mCharacterRigidBody = nullptr;
        const Kick_Engine::TransformComponent* mTransformComponent = nullptr;

        float mShiftSpeed = 10.0f;
        float mMoveSpeed = 1.0f;
        float mTurnSpeed = 0.1f;
    };
}
