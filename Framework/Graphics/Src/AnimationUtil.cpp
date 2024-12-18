#include "Precompiled.h"
#include "AnimationUtil.h"
#include "SimpleDraw.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;

namespace
{
    void ComputerBoneTransformRecursive(const Bone* bone, AnimationUtil::BoneTransforms& boneTransforms, const Animator* animator)
    {
        if (bone == nullptr)
        {
            return;
        }
        if (animator != nullptr)
        {
            boneTransforms[bone->index] = animator->GetToParentTransform(bone);
        }
        else
        {
            boneTransforms[bone->index] = bone->toParentTransform;
        }
        if (bone->parent != nullptr)
        {
            boneTransforms[bone->index] = boneTransforms[bone->index] * boneTransforms[bone->parentIndex];
        }

        for (const Bone* child : bone->children)
        {
            ComputerBoneTransformRecursive(child, boneTransforms, animator);
        }
    }
}

void AnimationUtil::ComputerBoneTransform(ModelId id, BoneTransforms& boneTransforms, const Animator* animator)
{
    // compute the world transform of the bone
    const Model* model = ModelManager::Get()->GetModel(id);
    if (model->skeleton != nullptr)
    {
        boneTransforms.resize(model->skeleton->bones.size(), Kick_Math::Matrix4::Identity);
    }
    ComputerBoneTransformRecursive(model->skeleton->root, boneTransforms, animator);

    // move skeleton up 
    for (auto& m : boneTransforms)
    {
        m._42 += 0.5f;
    }
}

void AnimationUtil::ApplyBoneOffsets(ModelId id, BoneTransforms& boneTransforms)
{
    // apply the offset transform of the bone
    const Model* model = ModelManager::Get()->GetModel(id);
    if (model != nullptr)
    {
        for (const auto& bone : model->skeleton->bones)
        {
            boneTransforms[bone->index] = bone->offsetTransform * boneTransforms[bone->index];
        }
    }
}

void AnimationUtil::DrawSkeleton(ModelId id, BoneTransforms& boneTransforms)
{
    // draw the bone
    const Model* model = ModelManager::Get()->GetModel(id);
    if (model->skeleton != nullptr)
    {
        for (auto& bone : model->skeleton->bones)
        {
            if (bone->parent != nullptr)
            {
                //get position of bone
                const Kick_Math::Vector3 posA = Kick_Math::GetTranslation(boneTransforms[bone->index]);
                const Kick_Math::Vector3 posB = Kick_Math::GetTranslation(boneTransforms[bone->parentIndex]);
                SimpleDraw::AddLine(posA, posB, Colors::Blue);
                SimpleDraw::AddSphere(4, 4, 0.03f, posA, Colors::Pink);
                // getposition of parent bone
                // SimpleDraw::AddLine(bonePos, parentBonePos, Colors::Blue);
                // SimpleDraw::AddSphere(10, 10, 0.03f, bonePos, 
                //const Kick_Math::Vector3 posA = Kick_Math::Get
            }
        }
    }
}
