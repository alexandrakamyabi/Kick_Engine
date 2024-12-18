#pragma once

#include "Animation.h"

namespace Kick_Engine::Graphics
{
    class AnimationBuilder
    {
    public:
        AnimationBuilder& AddPositionKey(const Kick_Math::Vector3& pos, float time, EaseType easeType = EaseType::Linear);
        AnimationBuilder& AddRotationKey(const Kick_Math::Quaternion& rot, float time, EaseType easeType = EaseType::Linear);
        AnimationBuilder& AddScaleKey(const Kick_Math::Vector3& scale, float time, EaseType easeType = EaseType::Linear);
        AnimationBuilder& AddEventKey(AnimationCallback cb, float time);

        [[nodiscard]] Animation Build();
    private:
        Animation mWorkingCopy;
    };
}
