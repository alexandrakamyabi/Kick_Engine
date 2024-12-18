#include "Precompiled.h"
#include "PhysicsDebugDraw.h"

#include <Graphics/Inc/Colors.h>
#include <Graphics/Inc/SimpleDraw.h>

using namespace Kick_Engine;
using namespace Kick_Engine::Physics;
using namespace Kick_Engine::Graphics;

void PhysicsDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{     
    SimpleDraw::AddLine(ConvertToVector3(from), ConvertToVector3(to), ConvertToColor(color));
}     
     
void PhysicsDebugDraw::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{     
    // NOTHING HERE
}     
     
void PhysicsDebugDraw::reportErrorWarning(const char* warningString)
{     
    LOG("[PhysicsWarning] %s", warningString);
}     
     
void PhysicsDebugDraw::draw3dText(const btVector3& location, const char* textString)
{     
    // NOTHING HERE
}     
     
void PhysicsDebugDraw::setDebugMode(int debugMode)
{     
    mDebugMode = debugMode;
}     
     
int  PhysicsDebugDraw::getDebugMode() const
{
    return mDebugMode;
}
