#pragma once

#include "Common.h"
#include "Colors.h"

namespace Kick_Engine::Graphics
{
    constexpr uint32_t VE_Position            = 0x1 << 0;
    constexpr uint32_t VE_Normal            = 0x1 << 1;
    constexpr uint32_t VE_Tangent            = 0x1 << 2;
    constexpr uint32_t VE_Color                = 0x1 << 3;
    constexpr uint32_t VE_TexCoord            = 0x1 << 4;
    constexpr uint32_t VE_BlendIndex        = 0x1 << 5;
    constexpr uint32_t VE_BlendWeight        = 0x1 << 6;

    #define VERTEX_FORMAT(fmt)\
        static constexpr uint32_t Format = fmt;

    struct VertexP
    {
        VERTEX_FORMAT(VE_Position);
        Kick_Math::Vector3 position;
    };

    struct VertexPC
    {
        VERTEX_FORMAT(VE_Position | VE_Color);
        Kick_Math::Vector3 position;
        Color color;
    };

    struct VertexPX
    {
        VERTEX_FORMAT(VE_Position | VE_TexCoord);
        Kick_Math::Vector3 position;
        Kick_Math::Vector2 uvCoord;
    };

    struct Vertex
    {
        VERTEX_FORMAT(VE_Position | VE_Normal | VE_Tangent | VE_TexCoord | VE_BlendIndex | VE_BlendWeight);
        static constexpr int MaxBoneWeights = 4;

        Kick_Math::Vector3 position;
        Kick_Math::Vector3 normal;
        Kick_Math::Vector3 tangent;
        Kick_Math::Vector2 uvCoord;
        int boneIndices[MaxBoneWeights] = {};
        float boneWeights[MaxBoneWeights] = {};
    };
}
