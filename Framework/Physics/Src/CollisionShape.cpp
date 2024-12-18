#include "Precompiled.h"
#include "CollisionShape.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Physics;

CollisionShape::~CollisionShape()
{
    ASSERT(mCollisionShape == nullptr, "CollisionShape: must call terminate");
}

void CollisionShape::InitializeEmpty()
{
    ASSERT(mCollisionShape == nullptr, "CollisionShape: is already initialized");
    mCollisionShape = new btEmptyShape();
}

void CollisionShape::InitializeBox(const Kick_Engine::Kick_Math::Vector3& halfExtents)
{
    ASSERT(mCollisionShape == nullptr, "CollisionShape: is already initialized");
    mCollisionShape = new btBoxShape(ConvertTobtVector3(halfExtents));
}

void CollisionShape::InitializeSphere(float radius)
{
    ASSERT(mCollisionShape == nullptr, "CollisionShape: is already initialized");
    mCollisionShape = new btSphereShape(radius);
}

void CollisionShape::InitializeHull(const Kick_Engine::Kick_Math::Vector3& halfExtents, const Kick_Engine::Kick_Math::Vector3& origin)
{
    ASSERT(mCollisionShape == nullptr, "CollisionShape: is already initialized");
    btConvexHullShape* hullShape = new btConvexHullShape();
    std::vector<Kick_Math::Vector3> points =
    {
        {-halfExtents.x, -halfExtents.y, -halfExtents.z},
        {-halfExtents.x,  halfExtents.y, -halfExtents.z},
        { halfExtents.x,  halfExtents.y, -halfExtents.z},
        { halfExtents.x, -halfExtents.y, -halfExtents.z},
        {-halfExtents.x, -halfExtents.y,  halfExtents.z},
        {-halfExtents.x,  halfExtents.y,  halfExtents.z},
        { halfExtents.x,  halfExtents.y,  halfExtents.z},
        { halfExtents.x, -halfExtents.y,  halfExtents.z}
    };

    for (const Kick_Math::Vector3& point : points)
    {
        hullShape->addPoint(ConvertTobtVector3(point + origin), false);
    }
    hullShape->recalcLocalAabb();
    mCollisionShape = hullShape;
}

void CollisionShape::Terminate()
{
    SafeDelete(mCollisionShape);
}
