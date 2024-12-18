#pragma once

namespace Kick_Engine
{
    struct ParticleActivateData
    {
        float lifeTime = 0.0;
        Color startColor = Colors::White;
        Color endColor = Colors::White;
        Kick_Math::Vector3 startScale = Kick_Math::Vector3::One;
        Kick_Math::Vector3 endScale = Kick_Math::Vector3::One;
        Kick_Math::Vector3 position = Kick_Math::Vector3::Zero;
        Kick_Math::Vector3 velocity = Kick_Math::Vector3::Zero;
    };

    struct ParticleInfo
    {
        Color currentColor = Colors::White;
        Kick_Math::Vector3 currentScale = Kick_Math::Vector3::One;
    };
    class Particle
    {
    public:
        Particle() = default;

        virtual void Initialize();
        virtual void Terminate();

        virtual void Activate(const ParticleActivateData& data);
        virtual void Update(float deltaTime);

        bool IsActive() const;
        void GetCurrentInfo (ParticleInfo& info) const;
        const Graphics::Transform& GetTransform() const;

    protected:
        Graphics::Transform mTransform;
        Physics::RigidBody mRigidBody;
        Physics::CollisionShape mCollisionShape;
        ParticleActivateData mData;

        float mLifeTime = 0.0f;
    };
}