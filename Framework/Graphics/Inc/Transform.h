#pragma once

#include "Common.h"

namespace Kick_Engine::Graphics
{
    struct Transform
    {
        Kick_Engine::Kick_Math::Vector3 position = Kick_Engine::Kick_Math::Vector3::Zero;
        Kick_Engine::Kick_Math::Quaternion rotation = Kick_Engine::Kick_Math::Quaternion::Identity;
        Kick_Engine::Kick_Math::Vector3 scale = Kick_Engine::Kick_Math::Vector3::One;

        Kick_Engine::Kick_Math::Matrix4 GetMatrix4() const
        {
            Kick_Math::Matrix4 mat = Kick_Math::Matrix4::MatrixRotationQuaternion(rotation);
            return {
                Kick_Engine::Kick_Math::Matrix4::Scaling(scale) *
                Kick_Engine::Kick_Math::Matrix4::MatrixRotationQuaternion(rotation) *
                Kick_Engine::Kick_Math::Matrix4::Translation(position)
            };
        }
    };
}