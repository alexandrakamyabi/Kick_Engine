#pragma once

class btRigidBody;
class btSoftBody;

namespace Kick_Engine::Physics
{
    class PhysicsObject
    {
    public: 
        PhysicsObject() = default;
        virtual ~PhysicsObject() = default;

    protected:
        friend class PhysicsWorld;
        // will sync the physics world with the graphics world
        virtual void Update() = 0;
        virtual btRigidBody* GetRigidBody() { return nullptr; }
        virtual btSoftBody* GetSoftBody() { return nullptr; }
    };
}