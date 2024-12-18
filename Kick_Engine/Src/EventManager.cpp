#include "Precompiled.h"
#include "EventManager.h"

using namespace Kick_Engine;

namespace
{
    std::unique_ptr<EventManager> sEventManager;
}

void EventManager::StaticInitialize()
{
    ASSERT(sEventManager == nullptr, "EventManager: is already initialized");
    sEventManager = std::make_unique<EventManager>();
    sEventManager->Initialize();
}

void EventManager::StaticTerminate()
{
    if (sEventManager != nullptr)
    {
        sEventManager->Terminate();
        sEventManager.reset();
    }
}

EventManager* Kick_Engine::EventManager::Get()
{
    ASSERT(sEventManager == nullptr, "EventManager: is not initialized");
    return sEventManager.get();
}

void EventManager::Broadcast(const Event* event)
{
    EventManager::Get()->BroadcastPrivate(event);
}


EventManager::~EventManager()
{
}

void EventManager::Initialize()
{
    mListeners.clear();
}

void EventManager::Terminate()
{
    mListeners.clear();
}

uint32_t EventManager::AddListener(EventType eventType, const EventCallback& cb)
{
    mListeners[eventType][++mListenerId] = cb;
    return mListenerId;
}
void EventManager::RemoveListener(EventType eventType, uint32_t listenerId)
{
    auto& listeners = mListeners[eventType];
    auto iter = listeners.find(listenerId);
    if (iter != listeners.end())
    {
        listeners.erase(iter);
    }
}

void EventManager::BroadcastPrivate(const Event* event)
{
    auto& listeners = mListeners[event->GetType()];
    for (auto& cb : listeners)
    {
        cb.second(event);
    }
}