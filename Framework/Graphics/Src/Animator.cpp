#include "Precompiled.h"
#include "Animator.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;

void Animator::Initialize(ModelId id)
{
    mModelId = id;
    mIsLooping = false;
    mAnimationTick = 0.0f;
    mClipIndex = -1;
}

void Animator::PlayAnimation(int clipIndex, bool looping)
{
    mClipIndex = clipIndex;
    mIsLooping = looping;
    mAnimationTick = 0.0f;
}

void Animator::Update(float deltaTime)
{
    if (mClipIndex < 0)
    {
        return;
    }

    const Model* model = ModelManager::Get()->GetModel(mModelId);
    const AnimationClip& animClip = model->animationClips[mClipIndex];
    mAnimationTick += animClip.ticksPerSecond * deltaTime;
    if (mAnimationTick > animClip.tickDuration)
    {
        if (mIsLooping)
        {
            while (mAnimationTick >= animClip.tickDuration)
            {
                mAnimationTick -= animClip.tickDuration;
            }
        }
        else
        {
            mAnimationTick = animClip.tickDuration;
        }
    }
}

bool Animator::IsFinished() const
{
    if (mIsLooping || mClipIndex < 0)
    {
        return false;
    }

    const Model* model = ModelManager::Get()->GetModel(mModelId);
    const AnimationClip& animClip = model->animationClips[mClipIndex];
    return mAnimationTick >= animClip.tickDuration;
}

Kick_Math::Vector3 Animator::GetRootPosition() const
{
    Kick_Math::Vector3 location = Kick_Math::Vector3::Zero;
    if (mClipIndex >= 0)
    {
        //const Model* model = ModelManager::Get()->GetModel(mModelId);
        //const AnimationClip& animClip = model->animationClips[mClipIndex];
        //Transform transform = animClip.boneAnimations[0]->GetTransform(mAnimationTick);
        //location = transform.position;
    }

    return location;
}

size_t Animator::GetAnimationCount() const
{
    const Model* model = ModelManager::Get()->GetModel(mModelId);
    return model->animationClips.size();
}

Kick_Math::Matrix4 Animator::GetToParentTransform(const Bone* bone) const
{
    if (mClipIndex < 0)
    {
        return bone->toParentTransform;
    }

    const Model* model = ModelManager::Get()->GetModel(mModelId);
    const AnimationClip& animClip = model->animationClips[mClipIndex];
    const Animation* animation = animClip.boneAnimations[bone->index].get();
    if (animation == nullptr)
    {
        return Kick_Math::Matrix4::Identity;
    }
    Transform transform = animation->GetTransform(mAnimationTick);
    return transform.GetMatrix4();
}
