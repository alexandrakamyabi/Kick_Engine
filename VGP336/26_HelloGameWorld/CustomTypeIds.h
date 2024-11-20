#pragma once

#include <Kick_Engine/Inc/Kick_Engine.h>

enum class CustomComponentId
{
	CustomDebugDraw = static_cast<uint32_t>(Kick_Engine::ComponentId::Count)
};

enum class CustomServiceId
{
	CustomDebugDrawDisplay = static_cast<uint32_t>(Kick_Engine::ServiceId::Count)
};