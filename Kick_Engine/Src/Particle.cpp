#include "Precompiled.h"
#include "Particle.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Kick_Math;
using namespace Kick_Engine::Graphics;

void Particle::Initialize()
{
    mLifeTime = 0.0f;
    mCollisionShape.InitializeEmpty();
    mTransform.position = { static_cast<float>(std::rand()), static_cast<float>(std::rand()),static_cast<float>(std::rand()) };
    mRigidBody.Initialize(mTransform, mCollisionShape, 0.1f);
}

void Particle::Terminate()
{
    mRigidBody.Terminate();
    mCollisionShape.Terminate();
}

void Particle::Activate(const ParticleActivateData& data)
{
    mData = data;
    mLifeTime = data.lifeTime;
    mRigidBody.SetPosition(data.position);
    mRigidBody.SetVelocity(data.velocity);
}

void Particle::Update(float deltaTime)
{
    mLifeTime -= deltaTime;
}

bool Particle::IsActive() const
{
    return mLifeTime > 0.0f;
}

void Kick_Engine::Particle::GetCurrentInfo(ParticleInfo& info) const
{
    if (mData.lifeTime > 0.0f)
    {
        float t = 1.0f - Clamp(mLifeTime / mData.lifeTime, 0.0f, 1.0f);
        info.currentColor = Lerp(mData.startColor, mData.endColor, t);
        info.currentScale = Lerp(mData.startScale, mData.endScale, t);
    }
}

const Graphics::Transform& Particle::GetTransform() const
{
    return mTransform;
}
