#pragma once

#include "Common.h"

namespace Kick_Engine::Graphics
{
    struct Bone
    {
        std::string name;
        int index = -1;

        Bone* parent = nullptr;
        int parentIndex = -1;

        std::vector<Bone*> children;
        std::vector<int> childrenIndices;

        Kick_Math::Matrix4 toParentTransform;
        Kick_Math::Matrix4 offsetTransform;
    };
}