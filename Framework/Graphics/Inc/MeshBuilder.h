#pragma once

#include "MeshTypes.h"

namespace Kick_Engine::Graphics
{
    class MeshBuilder
    {
    public:
        //cubes
        static MeshPC CreateCubePC(float size, const Color& color);
        static MeshPX CreateCubePX(float size);
        static Mesh CreateCube(float size);
        
        static MeshPX CreateSkyboxPX(float size);
        static MeshPX CreateSkySpherePX(int slices, int rings, float radius);
        //sphere
        static MeshPC CreateSpherePC(int slices, int rings, float radius);
        static MeshPX CreateSpherePX(int slices, int rings, float radius);
        static Mesh CreateSphere(int slices, int rings, float radius);

        //rect
        static MeshPC CreateRectPC(float width, float height, float depth);
        static MeshPX CreateRectPX(float width, float height, float depth);

        //plane
        static MeshPC CreatePlanePC(int numRows, int numCols, float spacing);
        static Mesh CreateGroundPlane(int numRows, int numCols, float spacing);

        //cylinder
        static MeshPC CreateCylinderPC(int slices, int rings);

        // ScreenQuad
        static MeshPX CreateScreenQuad();

        // Texture Quad
        static Mesh CreateSpriteQuad(float width, float height);
    };
}