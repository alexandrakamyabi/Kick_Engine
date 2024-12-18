#include "RenderObject.h"

//SKY SPHERE
void SkySphere::Initialize()
{
    MeshPX skySphere = MeshBuilder::CreateSkySpherePX(100, 100, 1000.0f);
    mMeshBuffer.Initialize(skySphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/Images/skysphere/space.jpg");

    mTransform = Matrix4::Identity;
}
void SkySphere::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void SkySphere::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = (useTransform) ? mTransform : Matrix4::Identity;
    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render(); 
    Texture::UnbindPS(0);
}
void SkySphere::Update(float deltaTime, float rotateSpeed)
{

}

//SUN SPHERE
void Sun::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 10.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/Images/planets/sun.jpg");

    mTransform = Matrix4::Identity;
}
void Sun::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Sun::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationX(gRotationX) * Matrix4::RotationY(gRotationY) * mTransform;
    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);
}
void Sun::Update(float deltaTime, float rotateSpeed)
{

}

//MERCURY SPHERE
void Mercury::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 1.5f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/Images/planets/mercury.jpg");

    mTransform = Matrix4::Identity;
}
void Mercury::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Mercury::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationX(gRotationX) * Matrix4::RotationY(gRotationY);
    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);
}
void Mercury::Update(float deltaTime, float rotateSpeed)
{
    gRotationY += Constants::HalfPi * deltaTime * rotateSpeed;
}

//VENUS SPHERE
void Venus::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 3.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/Images/planets/venus.jpg");

    mTransform = Matrix4::Identity;
}
void Venus::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Venus::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationX(gRotationX) * Matrix4::RotationY(gRotationY);    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);
}
void Venus::Update(float deltaTime, float rotateSpeed)
{
    gRotationY += Constants::HalfPi * deltaTime * rotateSpeed;
}

//EARTH SPHERE
void Earth::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 3.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/earth.jpg");

    mTransform = Matrix4::Identity;
}
void Earth::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Earth::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationX(gRotationX) * Matrix4::RotationY(gRotationY);    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);
}
void Earth::Update(float deltaTime, float rotateSpeed)
{
    gRotationY += Constants::HalfPi * deltaTime * rotateSpeed;
}

//MARS SPHERE
void Mars::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 2.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/Images/planets/mars.jpg");

    mTransform = Matrix4::Identity;
}
void Mars::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Mars::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationX(gRotationX) * Matrix4::RotationY(gRotationY);    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);
}
void Mars::Update(float deltaTime, float rotateSpeed)
{
    gRotationY += Constants::HalfPi * deltaTime * rotateSpeed;
}

//JUPITER SPHERE
void Jupiter::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 7.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/Images/planets/jupiter.jpg");

    mTransform = Matrix4::Identity;
}
void Jupiter::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Jupiter::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationX(gRotationX) * Matrix4::RotationY(gRotationY);    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);
}
void Jupiter::Update(float deltaTime, float rotateSpeed)
{
    gRotationY += Constants::HalfPi * deltaTime * rotateSpeed;
}

//SATURN SPHERE
void Saturn::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 6.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/Images/planets/saturn.jpg");

    mTransform = Matrix4::Identity;
}
void Saturn::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Saturn::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationX(gRotationX) * Matrix4::RotationY(gRotationY);    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);
}
void Saturn::Update(float deltaTime, float rotateSpeed)
{
    gRotationY += Constants::HalfPi * deltaTime * rotateSpeed;
}

//URANUS SPHERE
void Uranus::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 3.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/Images/planets/uranus.jpg");

    mTransform = Matrix4::Identity;
}
void Uranus::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Uranus::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationX(gRotationX) * Matrix4::RotationY(gRotationY);    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);
}
void Uranus::Update(float deltaTime, float rotateSpeed)
{
    gRotationY += Constants::HalfPi * deltaTime * rotateSpeed;
}

//NEPTUNE SPHERE
void Neptune::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 3.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/Images/planets/neptune.jpg");

    mTransform = Matrix4::Identity;
}
void Neptune::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Neptune::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationX(gRotationX) * Matrix4::RotationY(gRotationY);
    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);
}
void Neptune::Update(float deltaTime, float rotateSpeed)
{
    gRotationY += Constants::HalfPi * deltaTime * rotateSpeed;
}