#pragma once

#include "Event.h"

namespace Kick_Engine
{
    
    using EventCallback = std::function<void(const Event*)>;
    using EventListeners = std::map<EventType, std::map<uint32_t, EventCallback>>;

    class EventManager final
    {
    public:
        static void StaticInitialize();
        static void StaticTerminate();
        static EventManager* Get();
        static void Broadcast(const Event* event);

        EventManager() = default;
        ~EventManager();

        void Initialize();
        void Terminate();

        uint32_t AddListener(EventType eventType, const EventCallback& cb);
        void RemoveListener(EventType eventType, uint32_t listenerId);
    private:
        void BroadcastPrivate(const Event* event);

        EventListeners mListeners;
        uint32_t mListenerId = 0;
    };
}
