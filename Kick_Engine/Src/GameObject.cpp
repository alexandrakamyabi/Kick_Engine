#include "Precompiled.h"
#include "GameObject.h"

using namespace Kick_Engine;

static uint32_t gUniqueId = 0;

void GameObject::Initialize()
{
    ASSERT(!mInitialized, "GameObject: is already initialized");

    for (auto& component : mComponents)
    {
        component->Initialize();
    }

    mUniqueId = ++gUniqueId;
    mInitialized = true;
}

void GameObject::Terminate()
{
    for (auto& component : mComponents)
    {
        component->Terminate();
    }
}

void GameObject::DebugUI()
{
    if (ImGui::CollapsingHeader(mName.c_str()))
    {
        for (auto& component : mComponents)
        {
            component->DebugUI();
        }
    }
}

void GameObject::SetName(std::string& name)
{
    mName = std::move(name);
}

const std::string& GameObject::GetName() const
{
    return mName;
}

uint32_t GameObject::GetUniqueId() const
{
    return mUniqueId;
}

GameWorld& Kick_Engine::GameObject::GetWorld()
{
    return *mWorld;
}

const GameWorld& Kick_Engine::GameObject::GetWorld() const
{
    return *mWorld;
}

const GameObjectHandle& Kick_Engine::GameObject::GetHandle() const
{
    return mHandle;
}
