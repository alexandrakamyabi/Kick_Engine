#pragma once

#include "Keyframe.h"
#include "Transform.h"

namespace Kick_Engine::Graphics
{
    class Animation
    {
    public:
        Transform GetTransform(float time) const;
        float GetDuration() const;

        void PlayEvents(float prevTime, float currentTime);

    private:
        Kick_Math::Vector3 GetPosition(float time) const;
        Kick_Math::Quaternion GetRotation(float time) const;
        Kick_Math::Vector3 GetScale(float time) const;

        friend class AnimationBuilder;
        friend class AnimationIO;

        EventKeys mEventKeys;
        PositionKeys mPositionKeys;
        RotationKeys mRotationKeys;
        ScaleKeys mScaleKeys;
        float mDuration;
    };
}