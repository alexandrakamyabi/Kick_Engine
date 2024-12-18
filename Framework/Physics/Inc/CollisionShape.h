#pragma once


namespace Kick_Engine::Physics
{
    class CollisionShape final
    {
    public:
        CollisionShape() = default;
        ~CollisionShape();

        void InitializeEmpty();
        void InitializeBox(const Kick_Engine::Kick_Math::Vector3& halfExtents);
        void InitializeSphere(float radius);
        void InitializeHull(const Kick_Engine::Kick_Math::Vector3& halfExtents, const Kick_Engine::Kick_Math::Vector3& origin);
        void Terminate();

    private:
        btCollisionShape* mCollisionShape = nullptr;

        friend class RigidBody;
        btCollisionShape* GetCollisionShape() const { return mCollisionShape; }
    };
}