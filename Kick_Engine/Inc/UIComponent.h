#pragma once

#include "Component.h"

namespace Kick_Engine
{
    class UIComponent : public Component
    {
    public:
        virtual void Render() = 0;
    };
}