#pragma once
#include <Inc/Kick_Engine.h>

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Kick_Math;

class RenderObject
{
public:
    virtual void Initialize() {}
    virtual void Terminate() {}
    virtual void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) {}
    virtual void Update(float deltaTime, float rotateSpeed) {}
    virtual void SetPosition(const Vector3& pos) { mTransform._41 = pos.x; mTransform._42 = pos.y; mTransform._43 = pos.z; }
    Vector3 GetPosition() const 
    { 
        Matrix4 matWorld = mTransform * Matrix4::RotationX(gRotationX) * Matrix4::RotationY(gRotationY);
        return Vector3(matWorld._41, matWorld._42, matWorld._43);
    }

    virtual void DebugUI()
    {
        SimpleDraw::AddCircle(60, 10.0f, Colors::AliceBlue);
    }

protected:
    MeshBuffer mMeshBuffer;
    Texture mDiffuseTexture;
    Matrix4 mTransform;
    float gRotationX = 0.0f;
    float gRotationY = 0.0f;
};

class SkySphere : public RenderObject
{
public:
    void Initialize();
    void Terminate();
    void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
    void Update(float deltaTime, float rotateSpeed) override;

};

class Sun : public RenderObject
{
public:
    void Initialize();
    void Terminate();
    void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
    void Update(float deltaTime, float rotateSpeed) override;

};

class Mercury : public RenderObject
{
public:
    void Initialize();
    void Terminate();
    void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
    void Update(float deltaTime, float rotateSpeed) override;

};

class Venus : public RenderObject
{
public:
    void Initialize();
    void Terminate();
    void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
    void Update(float deltaTime, float rotateSpeed) override;

};

class Earth : public RenderObject
{
public:
    void Initialize();
    void Terminate();
    void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
    void Update(float deltaTime, float rotateSpeed) override;

};

class Mars : public RenderObject
{
public:
    void Initialize();
    void Terminate();
    void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
    void Update(float deltaTime, float rotateSpeed) override;

};

class Jupiter : public RenderObject
{
public:
    void Initialize();
    void Terminate();
    void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
    void Update(float deltaTime, float rotateSpeed) override;
};

class Saturn : public RenderObject
{
public:
    void Initialize();
    void Terminate();
    void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
    void Update(float deltaTime, float rotateSpeed) override;

};


class Uranus : public RenderObject
{
public:
    void Initialize();
    void Terminate();
    void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
    void Update(float deltaTime, float rotateSpeed) override;

};

class Neptune : public RenderObject
{
public:
    void Initialize();
    void Terminate();
    void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
    void Update(float deltaTime, float rotateSpeed) override;

};



