#pragma once

#include "Inc/AppState.h"
#include "Inc/Kick_Engine.h"

#include "RenderObject.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Kick_Math;
using namespace Kick_Engine::Graphics;


class GameState : public AppState
{

public:
    void Initialize();
    void Terminate();
    void Render();
    void Update(float deltaTime);
    void DebugUI();
protected:
    void RenderMesh(const Camera& camera, bool useTransform);

    //MeshBuffer mMeshBuffer;
    Camera mCamera;
    Camera mRenderTargetCamera;
    ConstantBuffer mConstantBuffer;
    VertexShader mVertexShader;
    PixelShader mPixelShader;
    RenderTarget mRenderTarget;

    SkySphere mSkySphere;

    //PLANETS
    Sun mSun;
    Mercury mMercury;
    Venus mVenus;
    Earth mEarth;
    Earth mEarth2;
    Mars mMars;
    Jupiter mJupiter;
    Saturn mSaturn;
    Uranus mUranus;
    Neptune mNeptune;

    enum Planets
    {
        Sun,
        Mercury,
        Venus,
        Earth,
        Mars,
        Jupiter,
        Saturn,
        Uranus,
        Neptune
    };

    Planets mTarget;

    //Texture mDiffuseTexture;
    Sampler mSampler;
    Matrix4 mWorldTrans;

    bool mDrawWorld = true;
    bool mDrawSphereSun = true;
    bool mDrawSphereMercury = true;
    bool mDrawSphereVenus = true;
    bool mDrawSphereEarth = true;
    bool mDrawSphereMars = true;
    bool mDrawSphereJupiter = true;
    bool mDrawSphereSaturn = true;
    bool mDrawSphereUranus = true;
    bool mDrawSphereNeptune = true;

    Color mSphere1Color = Colors::Pink;
    Color mSphere2Color = Colors::Aqua;

    Vector3 offset = { 20.0f, 10.0f, 0.0f };


    //Rotate speed
    float gRotateMercury = 0.9f;
    float gRotateVenus = 0.8f;
    float gRotateEarth = 0.7f;
    float gRotateMars = 0.6f;
    float gRotateJupiter = 0.5f;
    float gRotateSaturn = 0.4f;
    float gRotateUranus = 0.3f;
    float gRotateNeptune = 0.2f;

    //Draw circle planets
    bool mCircleWorld = true;
    bool mCircleSphereSun = true;
    bool mCircleSphereMercury = true;
    bool mCircleSphereVenus = true;
    bool mCircleSphereEarth = true;
    bool mCircleSphereMars = true;
    bool mCircleSphereJupiter = true;
    bool mCircleSphereSaturn = true;
    bool mCircleSphereUranus = true;
    bool mCircleSphereNeptune = true;
};

