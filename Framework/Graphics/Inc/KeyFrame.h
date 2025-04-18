#pragma once

#include "Common.h"

namespace Kick_Engine::Graphics
{
    enum class EaseType
    {
        Linear,
        EaseInQuad,
        EaseOutQuad,
        EaseInOutQuad
    };

    template<class T>
    struct Keyframe
    {
        Keyframe() = default;
        Keyframe(const T& k, float t, EaseType e = EaseType::Linear)
            : key(k)
            , time(t)
            , easeType(e)
        {

        }
        T key = T();
        float time = 0.0f;
        EaseType easeType = EaseType::Linear;
    };

    using AnimationCallback = std::function<void()>;

    template<class T>
    using Keyframes = std::vector<Keyframe<T>>;

    using PositionKeys = Keyframes<Kick_Math::Vector3>;
    using RotationKeys = Keyframes<Kick_Math::Quaternion>;
    using ScaleKeys = Keyframes<Kick_Math::Vector3>;
    using EventKeys = Keyframes<AnimationCallback>;
}