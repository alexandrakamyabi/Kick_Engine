#pragma once

#include "ModelManager.h"
#include "Animator.h"

namespace Kick_Engine::Graphics::AnimationUtil
{
    using BoneTransforms = std::vector<Kick_Math::Matrix4>;

    void ComputerBoneTransform(ModelId id, BoneTransforms& boneTransforms, const Animator* animatior = nullptr);
    void ApplyBoneOffsets(ModelId id, BoneTransforms& boneTransforms);
    void DrawSkeleton(ModelId id, BoneTransforms& boneTransforms);
}