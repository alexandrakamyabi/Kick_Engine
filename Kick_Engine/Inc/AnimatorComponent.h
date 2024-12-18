#pragma once

#include "Component.h"

namespace Kick_Engine
{
    class AnimatorComponent final : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::Animator);

        void Initialize() override;
        void Terminate() override;
        void Update(float deltaTime) override;
        void DebugUI() override;
        void Deserialize(const rapidjson::Value& value) override;
        bool IsFinished();

        Vector3 GetRootPosition() const;
        bool Play(int index, bool looping = false);
        Graphics::Animator& GetAnimator();
        const Graphics::Animator& GetAnimator() const;

    private:
        int mStartPlayIndex = 1;
        Graphics::Animator mAnimator;
    };
}
