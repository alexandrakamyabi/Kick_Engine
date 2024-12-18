#include "TPSCameraComponent.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Kick_Math;
using namespace Kick_Engine::Input;

void TPSCameraComponent::Initialize()
{
    UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
    ASSERT(updateService != nullptr, "TPSCameraComponent: game world requires an update service");
    updateService->Register(this);

    mCameraComponent = GetOwner().GetComponent<CameraComponent>();
    mCharacterRigidBody = GetOwner().GetComponent<RigidBodyComponent>();
    mTransformComponent = GetOwner().GetComponent<TransformComponent>();
}
void TPSCameraComponent::Terminate()
{
    UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
    ASSERT(updateService != nullptr, "TPSCameraComponent: game world requires an update service");
    updateService->Unregister(this);

    mCameraComponent = nullptr;
}

void TPSCameraComponent::Update(float deltaTime)
{
    Camera& camera = mCameraComponent->GetCamera();

    Matrix4 mat = mTransformComponent->GetMatrix4();
    Vector3 pos = Kick_Math::GetTranslation(mat);
    Vector3 fwd = Kick_Math::GetLook(mat);
    Vector3 right = Kick_Math::GetRight(mat);
    Vector3 up = Kick_Math::GetUp(mat);

    Vector3 targetCameraPos = pos + (up * 2.0f) + (fwd * 5.3f) + (-right * 0.2f);
    Vector3 cameraPos = Lerp(camera.GetPosition(), targetCameraPos, deltaTime / 0.2f);
    camera.SetPosition(cameraPos);
    camera.SetLookAt(cameraPos + -fwd);
}

void TPSCameraComponent::Deserialize(const rapidjson::Value& value)
{
    if (value.HasMember("MoveSpeed"))
    {
        mMoveSpeed = value["MoveSpeed"].GetFloat();
    }
    if (value.HasMember("TurnSpeed"))
    {
        mTurnSpeed = value["TurnSpeed"].GetFloat();
    }
    if (value.HasMember("ShiftSpeed"))
    {
        mShiftSpeed = value["ShiftSpeed"].GetFloat();
    }
}

