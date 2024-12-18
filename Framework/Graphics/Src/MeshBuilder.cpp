#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;

namespace
{
    Color GetNextColor(int& index)
    {
        constexpr Color colorTable[] = {
            Colors::DarkBlue,
            Colors::Aqua,
            Colors::LightGreen,
            Colors::PapayaWhip,
            Colors::Silver,
            Colors::Orange,
            Colors::Green,
            Colors::Red
        };

        index = (index + 1) % std::size(colorTable);
        return colorTable[index];
    }
    void CreateCubeIndices(std::vector<uint32_t>& indices)
    {
        indices = {
            //front
            0, 1, 2,
            0, 2, 3,

            //back
            7, 6, 5,
            7, 5, 4,

            //right
            3, 2, 6,
            3, 6, 7,

            //left
            0, 5, 1,
            0, 4, 5,

            //top
            1, 5, 6,
            1, 6, 2,

            //bottom
            0, 3, 7,
            0, 7, 4
        };
    }

    void CreateSkyboxIndices(std::vector<uint32_t>& indices)
    {
        indices = {
            //front
            0, 2, 1,
            0, 3, 2,

            //back
            7, 5, 6,
            7, 4, 5,


            //top
            8, 10, 9,
            8, 11, 10,

            //bottom
            12, 13, 14,
            12, 14, 15,
            
            //right
            3, 6, 2,
            3, 7, 6,

            //left
            0, 1, 5,
            0, 5, 4
        };
    }

    void CreatePlaneIndices(std::vector<uint32_t>& indices, int numRows, int numColumns)
    {
        for (int r = 0; r < numRows; ++r)
        {
            for (int c = 0; c < numColumns; ++c)
            {
                uint32_t i = (r * (numColumns + 1)) + c;

                //triangle 1
                indices.push_back(i);
                indices.push_back(i + numColumns + 2);
                indices.push_back(i + 1);

                //triangle 2
                indices.push_back(i);
                indices.push_back(i + numColumns + 1);
                indices.push_back(i + numColumns + 2);
            }
        }
    }

    void CreateCapIndices(std::vector<uint32_t>& indices, int slices, int topIndex, int bottomIndex)
    {
        for (int s = 0; s < slices; ++s)
        {
            //bottom triangle
            indices.push_back(s);
            indices.push_back(s + 1);
            indices.push_back(bottomIndex);

            //top triangle
            int topRowStartIndex = topIndex - slices - 1 + s;
            indices.push_back(topIndex);
            indices.push_back(topRowStartIndex + 1);
            indices.push_back(topRowStartIndex);
        }

    }    
}

//cubes
MeshPC MeshBuilder::CreateCubePC(float size, const Color& color)
{
    MeshPC mesh;

    const float hs = size * 0.5f;
    //front
    mesh.vertices.push_back({ { -hs, -hs, -hs }, color }); //0
    mesh.vertices.push_back({ { -hs, hs, -hs }, color }); //1
    mesh.vertices.push_back({ { hs, hs, -hs }, color }); //2
    mesh.vertices.push_back({ { hs, -hs, -hs }, color }); //3

    //back
    mesh.vertices.push_back({ { -hs, -hs, hs }, color }); //4
    mesh.vertices.push_back({ { -hs, hs, hs }, color }); //5
    mesh.vertices.push_back({ { hs, hs, hs }, color }); //6
    mesh.vertices.push_back({ { hs, -hs, hs }, color }); //7

    CreateCubeIndices(mesh.indices);
    

    return mesh;
}
MeshPX MeshBuilder::CreateCubePX(float size)
{
    MeshPX mesh;

    const float hs = size * 0.5f;
    //front
    mesh.vertices.push_back({ { -hs, -hs, -hs }, {0.25f, 0.66f } }); //0
    mesh.vertices.push_back({ { -hs, hs, -hs }, {0.25f, 0.33f } }); //1
    mesh.vertices.push_back({ { hs, hs, -hs }, {0.5f, 0.33f } }); //2
    mesh.vertices.push_back({ { hs, -hs, -hs }, {0.5f, 0.66f } }); //3

    //back
    mesh.vertices.push_back({ { -hs, -hs, hs }, {0.25f, 1.0f} }); //4
    mesh.vertices.push_back({ { -hs, hs, hs }, {0.0f, 0.33f} }); //5
    mesh.vertices.push_back({ { hs, hs, hs }, {0.5f, 0.0f} }); //6
    mesh.vertices.push_back({ { hs, -hs, hs }, {0.5f, 1.0f} }); //7

    CreateCubeIndices(mesh.indices);
    return mesh;
}
MeshPX MeshBuilder::CreateSkyboxPX(float size)
{
    MeshPX mesh;

    // Create al the vertices for each face
    // apply the UV coords for each face
    // x >> 0.0f, 0.25f, 0.5f, 0.75f
    // y >> 0.0f, 0.33f, 0.66f, 1.0f
    // create the faces and add indices or just use vertices

    const float hs = size * 0.5f;
    //front
    mesh.vertices.push_back({ { -hs, -hs, -hs }, {0.0f, 0.668f } }); //0
    mesh.vertices.push_back({ { -hs, hs, -hs }, {0.0f, 0.335f } }); //1
    mesh.vertices.push_back({ { hs, hs, -hs }, {0.25f, 0.335f } }); //2
    mesh.vertices.push_back({ { hs, -hs, -hs }, {0.25f, 0.668f } }); //3

    //back
    mesh.vertices.push_back({ { -hs, -hs, hs }, {0.5f, 0.668f} }); //4
    mesh.vertices.push_back({ { -hs, hs, hs }, {0.5f, 0.335f} }); //5
    mesh.vertices.push_back({ { hs, hs, hs }, {0.75f, 0.335f} }); //6
    mesh.vertices.push_back({ { hs, -hs, hs }, {0.75f, 0.668f} }); //7

    //top
    mesh.vertices.push_back({ { -hs, hs, -hs }, {0.25f, 0.335f } }); //0
    mesh.vertices.push_back({ { -hs, hs, hs }, {0.5f, 0.335f } }); //1
    mesh.vertices.push_back({ { hs, hs, hs }, {0.5f, 0.0f } }); //2
    mesh.vertices.push_back({ { hs, hs, -hs }, {0.25f, 0.0f } }); //3

    //bottom
    mesh.vertices.push_back({ { -hs, -hs, -hs }, {0.25f, 1.0f} }); //4
    mesh.vertices.push_back({ { -hs, -hs, hs }, {0.25f, 0.668f} }); //5
    mesh.vertices.push_back({ { hs, -hs, hs }, {0.5f, 0.668f} }); //6
    mesh.vertices.push_back({ { hs, -hs, -hs }, {0.5f, 1.0f} }); //7

    CreateSkyboxIndices(mesh.indices);
    return mesh;
}

MeshPX MeshBuilder::CreateSkySpherePX(int slices, int rings, float radius)
{
    MeshPX mesh;

    float vertRotation = (Kick_Math::Constants::Pi / static_cast<float>(rings - 1));
    float horzRotation = (Kick_Math::Constants::TwoPi / static_cast<float>(slices));
    float uStep = 1.0f / static_cast<float>(slices);
    float vStep = 1.0f / static_cast<float>(rings);

    for (int r = 0; r <= rings; r++)
    {
        float ring = static_cast<float>(r);
        float phi = ring * vertRotation;
        for (int s = 0; s <= slices; s++)
        {
            float slice = static_cast<float>(s);
            float rotation = slice * horzRotation;

            float u = 1.0f - (uStep * slice);
            float v = vStep * ring;
            mesh.vertices.push_back({ {
                radius * cos(rotation) * sin(phi),
                radius * cos(phi),
                radius * sin(rotation) * sin(phi)
            },
                {u,v } });
        }

    }
    CreatePlaneIndices(mesh.indices, rings, slices);

    return mesh;
}

Mesh MeshBuilder::CreateCube(float size)
{
    Mesh mesh;
    return mesh;
}

//sphere
MeshPC MeshBuilder::CreateSpherePC(int slices, int rings, float radius)
{
    MeshPC mesh;
    int index = rand() % 100;



    float vertRotation = (Kick_Math::Constants::Pi / static_cast<float>(rings - 1));
    float horzRotation = (Kick_Math::Constants::TwoPi / static_cast<float>(slices));
    for (int r = 0; r <= rings; r++)
    {
        float ring = static_cast<float>(r);
        float phi = ring * vertRotation;
        for (int s = 0; s <= slices; s++)
        {
            float slice = static_cast<float>(s);
            float rotation = slice * horzRotation;

            mesh.vertices.push_back({ {
                radius * sin(rotation) * sin(phi),
                radius * cos(phi),
                radius * cos(rotation) * sin(phi)
            },
            GetNextColor(index) });
        }

    }
    CreatePlaneIndices(mesh.indices, rings, slices);

    return mesh;
}
MeshPX MeshBuilder::CreateSpherePX(int slices, int rings, float radius)
{
    MeshPX mesh;

    float vertRotation = (Kick_Math::Constants::Pi / static_cast<float>(rings - 1));
    float horzRotation = (Kick_Math::Constants::TwoPi / static_cast<float>(slices));
    float uStep = 1.0f / static_cast<float>(slices);
    float vStep = 1.0f / static_cast<float>(rings);

    for (int r = 0; r <= rings; r++)
    {
        float ring = static_cast<float>(r);
        float phi = ring * vertRotation;
        for (int s = 0; s <= slices; s++)
        {
            float slice = static_cast<float>(s);
            float rotation = slice * horzRotation;

            float u = 1.0f - (uStep * slice);
            float v = vStep * ring;
            mesh.vertices.push_back({ {
                radius * sin(rotation) * sin(phi),
                radius * cos(phi),
                radius * cos(rotation) * sin(phi)
            },
                {u,v } });
        }

    }
    CreatePlaneIndices(mesh.indices, rings, slices);

    return mesh;
}
Mesh MeshBuilder::CreateSphere(int slices, int rings, float radius)
{
    
    Mesh mesh;

    float vertRotation = (Kick_Math::Constants::Pi / static_cast<float>(rings - 1));
    float horzRotation = (Kick_Math::Constants::TwoPi / static_cast<float>(slices));
    float uStep = 1.0f / static_cast<float>(slices);
    float vStep = 1.0f / static_cast<float>(rings);

    for (int r = 0; r <= rings; r++)
    {
        float ring = static_cast<float>(r);
        float phi = ring * vertRotation;
        for (int s = 0; s <= slices; s++)
        {
            float slice = static_cast<float>(s);
            float rotation = slice * horzRotation;

            float u = 1.0f - (uStep * slice);
            float v = vStep * ring;

            float x = radius * sin(rotation) * sin(phi);
            float y = radius * cos(phi);
            float z = radius * cos(rotation) * sin(phi);
            Kick_Math::Vector3 position = {x,y,z};
            Kick_Math::Vector3 normal = Kick_Math::Normalize(position);
            Kick_Math::Vector3 tangent = Kick_Math::Normalize({-z, 0.0f, x});
            Kick_Math::Vector2 uvCoord = {u , v};

            mesh.vertices.push_back({ 
                position,
                normal,
                tangent,
                uvCoord });
        }

    }
    CreatePlaneIndices(mesh.indices, rings, slices);

    return mesh;
}

//rect
MeshPC MeshBuilder::CreateRectPC(float width, float height, float depth)
{
    MeshPC mesh;
    int index = rand() % 100;
    const float hw = width * 0.5f; // x
    const float hh = height * 0.5f;// y
    const float hd = depth * 0.5f; // z

    //front
    mesh.vertices.push_back({ { -hw, -hh, -hd }, GetNextColor(index) }); //0
    mesh.vertices.push_back({ { -hw, hh, -hd }, GetNextColor(index) }); //1
    mesh.vertices.push_back({ { hw, hh, -hd }, GetNextColor(index) }); //2
    mesh.vertices.push_back({ { hw, -hh, -hd }, GetNextColor(index) }); //3

    //back
    mesh.vertices.push_back({ { -hw, -hh, hd }, GetNextColor(index) }); //4
    mesh.vertices.push_back({ { -hw, hh, hd }, GetNextColor(index) }); //5
    mesh.vertices.push_back({ { hw, hh, hd }, GetNextColor(index) }); //6
    mesh.vertices.push_back({ { hw, -hh, hd }, GetNextColor(index) }); //7

    CreateCubeIndices(mesh.indices);

    return mesh;
}
MeshPX MeshBuilder::CreateRectPX(float width, float height, float depth)
{
    MeshPX mesh;
    const float hw = width * 0.5f; // x
    const float hh = height * 0.5f;// y
    const float hd = depth * 0.5f; // z

    // implement
    //front
    mesh.vertices.push_back({ { -hw, -hh, -hd }, {0.25f, 0.66f } }); //0
    mesh.vertices.push_back({ { -hw, hh, -hd }, {0.25f, 0.33f } }); //1
    mesh.vertices.push_back({ { hw, hh, -hd }, {0.5f, 0.33f } }); //2
    mesh.vertices.push_back({ { hw, -hh, -hd }, {0.5f, 0.66f } }); //3

    //back
    mesh.vertices.push_back({ { -hw, -hh, hd }, {0.25f, 1.0f} }); //4
    mesh.vertices.push_back({ { -hw, hh, hd }, {0.0f, 0.33f} }); //5
    mesh.vertices.push_back({ { hw, hh, hd }, {0.5f, 0.0f} }); //6
    mesh.vertices.push_back({ { hw, -hh, hd },  {0.5f, 1.0f} }); //7

    return mesh;
}

//plane
MeshPC MeshBuilder::CreatePlanePC(int numRows, int numCols, float spacing)
{
    MeshPC mesh;
    int index = rand() % 100;

    const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
    const float hph = static_cast<float>(numRows) * spacing * 0.5f;

    float x = -hpw;
    float y = -hph;

    for (int r = 0; r <= numRows; r++)
    {
        for (int c = 0; c <= numCols; c++)
        {
            mesh.vertices.push_back({{x,y,0.0f}, GetNextColor(index)});
            x += spacing;
        }
        x = -hpw;
        y += spacing;
    }

    CreatePlaneIndices(mesh.indices, numRows, numCols);

    return mesh;
}

Mesh MeshBuilder::CreateGroundPlane(int numRows, int numCols, float spacing)
{
    Mesh mesh;
    int index = rand() % 100;

    const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
    const float hph = static_cast<float>(numRows) * spacing * 0.5f;
    const float uInc = 1.0f / static_cast<float>(numCols);
    const float vInc = 1.0f / static_cast<float>(numRows);

    float x = -hpw;
    float z = -hph;
    float u = 0.0f;
    float v = 1.0f;

    for (int r = 0; r <= numRows; r++)
    {
        for (int c = 0; c <= numCols; c++)
        {
            mesh.vertices.push_back({ 
                {x , 0.0f , z}, 
                {0.0f, 1.0f, 0.0f},
                {0.0f, 0.0f, 1.0f}, 
                {u ,v}});
            x += spacing;
            u += uInc;
        }
        x = -hpw;
        z += spacing;
        u = 0.0f;
        v -= vInc;
    }

    CreatePlaneIndices(mesh.indices, numRows, numCols);

    return mesh;
}

//cylinder
MeshPC MeshBuilder::CreateCylinderPC(int slices, int rings)
{
    MeshPC mesh;

    int index = rand() % 100;
    const float hh = static_cast<float>(rings) * 0.5f;

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);
        for (int s = 0; s <= slices; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = (slice / static_cast<float>(slices)) * Kick_Math::Constants::TwoPi;

            mesh.vertices.push_back({ {
                    sin(rotation),
                    ring - hh,
                    -cos(rotation)},
                    GetNextColor(index) });
        }
    }

    mesh.vertices.push_back({ { 0.0f, hh, 0.0f }, GetNextColor(index) });
    mesh.vertices.push_back({ { 0.0f, -hh, 0.0f }, GetNextColor(index) });

    CreatePlaneIndices(mesh.indices, rings, slices);
    CreateCapIndices(mesh.indices, slices, mesh.vertices.size() - 2, mesh.vertices.size() - 1);

    return mesh;
}

MeshPX MeshBuilder::CreateScreenQuad()
{
    MeshPX mesh;
    mesh.vertices.push_back({ {-1.0f, -1.0f, 0.0f}, {0.0f, 1.0f} });
    mesh.vertices.push_back({ {-1.0f, 1.0f, 0.0f}, {0.0f, 0.0f} });
    mesh.vertices.push_back({ {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f} });
    mesh.vertices.push_back({ {1.0f, -1.0f, 0.0f}, {1.0f, 1.0f} });
    mesh.indices = { 0, 1, 2, 0, 2, 3 };

    return mesh;
}

Mesh MeshBuilder::CreateSpriteQuad(float width, float height)
{
    Mesh mesh;
    float hw = width * 0.5f;
    float hh = height * 0.5f;

    mesh.vertices.push_back({{ -hw, -hh, 0.0f }, -Kick_Math::Vector3::ZAxis, Kick_Math::Vector3::XAxis, { 0.0f, 1.0f }});
    mesh.vertices.push_back({{ -hw, hh, 0.0f }, -Kick_Math::Vector3::ZAxis, Kick_Math::Vector3::XAxis, { 0.0f, 0.0f }});
    mesh.vertices.push_back({{ hw, hh, 0.0f }, -Kick_Math::Vector3::ZAxis, Kick_Math::Vector3::XAxis, { 1.0f, 0.0f }});
    mesh.vertices.push_back({{ hw, -hh, 0.0f }, -Kick_Math::Vector3::ZAxis, Kick_Math::Vector3::XAxis, { 1.0f, 1.0f }});

    mesh.indices = {
        0, 1, 2,
        0, 2, 3
    };

    return mesh;
}