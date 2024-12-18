#pragma once

#include "Bone.h"

namespace Kick_Engine::Graphics
{
    struct Skeleton
    {
        Bone* root = nullptr;
        std::vector<std::unique_ptr<Bone>> bones;
    };
}