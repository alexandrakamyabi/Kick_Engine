#include "Precompiled.h"
#include "RenderObject.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;

void RenderObject::Terminate()
{
	meshBuffer.Terminate();
}