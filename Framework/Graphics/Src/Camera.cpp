#include "Precompiled.h"
#include "Camera.h"

#include "GraphicsSystem.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;

void Camera::SetMode(ProjectionMode mode)
{
    mProjectionMode = mode;
}

void Camera::SetPosition(const Kick_Math::Vector3& position)
{
    mPosition = position;
}

void Camera::SetDirection(const Kick_Math::Vector3& direction)
{
    // Prevent setting direction straight up or down
    auto dir = Kick_Math::Normalize(direction);
    if (Kick_Math::Abs(Kick_Math::Dot(dir, Kick_Math::Vector3::YAxis)) < 0.995f)
        mDirection = dir;
}

void Camera::SetLookAt(const Kick_Math::Vector3& target)
{
    SetDirection(target - mPosition);
}

void Camera::SetFov(float fov)
{
    constexpr float kMinFov = 10.0f * Kick_Math::Constants::DegToRad;
    constexpr float kMaxFov = 170.0f * Kick_Math::Constants::DegToRad;
    mFov = Kick_Math::Clamp(fov, kMinFov, kMaxFov);
}

void Camera::SetAspectRatio(float ratio)
{
    mAspectRatio = ratio;
}

void Camera::SetSize(float width, float height)
{
    mWidth = width;
    mHeight = height;
}

void Camera::SetNearPlane(float nearPlane)
{
    mNearPlane = nearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
    mFarPlane = farPlane;
}

void Camera::Walk(float distance)
{
    mPosition += mDirection * distance;
}

void Camera::Strafe(float distance)
{
    const Kick_Math::Vector3 right = Kick_Math::Normalize(Cross(Kick_Math::Vector3::YAxis, mDirection));
    mPosition += right * distance;
}

void Camera::Rise(float distance)
{
    mPosition += Kick_Math::Vector3::YAxis * distance;
}

void Camera::Yaw(float radian)
{
    Kick_Math::Matrix4 matRotate = Kick_Math::Matrix4::RotationY(radian);
    mDirection = Kick_Math::TransformNormal(mDirection, matRotate);
}

void Camera::Pitch(float radian)
{
    const Kick_Math::Vector3 right = Kick_Math::Normalize(Cross(Kick_Math::Vector3::YAxis, mDirection));
    const Kick_Math::Matrix4 matRot = Kick_Math::Matrix4::RotationAxis(right, radian);
    const Kick_Math::Vector3 newLook = Kick_Math::TransformNormal(mDirection, matRot);
    SetDirection(newLook);
}

void Camera::Zoom(float amount)
{
    constexpr float minZoom = 170.0f * Kick_Math::Constants::DegToRad;
    constexpr float maxZoom = 10.0f * Kick_Math::Constants::DegToRad;
    mFov = Kick_Math::Clamp(mFov - amount, maxZoom, minZoom);
}

const Kick_Math::Vector3& Camera::GetPosition() const
{
    return mPosition;
}

const Kick_Math::Vector3& Camera::GetDirection() const
{
    return mDirection;
}

Kick_Math::Matrix4 Camera::GetViewMatrix() const
{
    const Kick_Math::Vector3 l = mDirection;
    const Kick_Math::Vector3 r = Kick_Math::Normalize(Kick_Math::Cross(Kick_Math::Vector3::YAxis, l));
    const Kick_Math::Vector3 u = Kick_Math::Normalize(Kick_Math::Cross(l, r));
    const float x = -Kick_Math::Dot(r, mPosition);
    const float y = -Kick_Math::Dot(u, mPosition);
    const float z = -Kick_Math::Dot(l, mPosition);

    return
    {
        r.x, u.x, l.x, 0.0f,
        r.y, u.y, l.y, 0.0f,
        r.z, u.z, l.z, 0.0f,
        x,   y,   z,   1.0f
    };
}

Kick_Math::Matrix4 Camera::GetProjectionMatrix() const
{
    return (mProjectionMode == ProjectionMode::Perspective) ? GetPerspectiveMatrix() : GetOrthographicMatrix();
}

Kick_Math::Matrix4 Camera::GetPerspectiveMatrix() const
{
    const float a = (mAspectRatio == 0.0f) ? GraphicsSystem::Get()->GetBackBufferAspectRatio() : mAspectRatio;
    const float h = 1.0f / tan(mFov * 0.5f);
    const float w = h / a;
    const float zf = mFarPlane;
    const float zn = mNearPlane;
    const float q = zf / (zf - zn);

    return {
        w,    0.0f, 0.0f,    0.0f,
        0.0f, h,    0.0f,    0.0f,
        0.0f, 0.0f, q,       1.0f,
        0.0f, 0.0f, -zn * q, 0.0f
    };
}

Kick_Math::Matrix4 Camera::GetOrthographicMatrix() const
{
    const float w = (mWidth == 0.0f) ? GraphicsSystem::Get()->GetBackBufferWidth() : mWidth;
    const float h = (mHeight == 0.0f) ? GraphicsSystem::Get()->GetBackBufferHeight() : mHeight;
    const float f = mFarPlane;
    const float n = mNearPlane;
    return     {
        2 / w, 0.0f,  0.0f,        0.0f,
        0.0f,  2 / h, 0.0f,        0.0f,
        0.0f,  0.0f,  1 / (f - n), 0.0f,
        0.0f,  0.0f,  n / (n - f), 1.0f
    };
}