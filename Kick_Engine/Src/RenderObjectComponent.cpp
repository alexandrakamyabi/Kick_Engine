#include "Precompiled.h"
#include "RenderObjectComponent.h"

#include "GameWorld.h"
#include "RenderService.h"

using namespace Kick_Engine;

void RenderObjectComponent::Initialize()
{
	RenderService* renderService = GetOwner().GetWorld().GetService<RenderService>();
	renderService->Register(this);
}

void RenderObjectComponent::Terminate()
{
	RenderService* renderService = GetOwner().GetWorld().GetService<RenderService>();
	renderService->Unregister(this);
}

void Kick_Engine::RenderObjectComponent::Deserialize(const rapidjson::Value& value)
{
	if (value.HasMember("CastShadow"))
	{
		mCastShadow = value["CastShadow"].GetBool();
	}
}

bool RenderObjectComponent::CastShadow() const
{
	return mCastShadow;
}
