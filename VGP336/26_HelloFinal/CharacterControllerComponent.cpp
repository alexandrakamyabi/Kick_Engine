#include "CharacterControllerComponent.h"
#include "TPSCameraComponent.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Input;

void CharacterControllerComponent::Initialize()
{
	mCharacterAnimation = GetOwner().GetComponent<AnimatorComponent>();
	mCharacterRigidBody = GetOwner().GetComponent<RigidBodyComponent>();
	mCharacterTransform = GetOwner().GetComponent<TransformComponent>();

	UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
	updateService->Register(this);
}

void CharacterControllerComponent::Terminate()
{
	UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
	updateService->Unregister(this);
}

void CharacterControllerComponent::Update(float deltaTime)
{
	InputSystem* input = InputSystem::Get();
	Matrix4 transform = mCharacterTransform->GetMatrix4();
	Vector3 pos = Kick_Math::GetTranslation(transform);
	Vector3 foward = Kick_Math::GetLook(transform);
	Vector3 right = Kick_Math::GetRight(transform);
	Vector3 velocity = Vector3::Zero;
	Vector3 currentVelocity = mCharacterRigidBody->GetVelocity();
	int AnimationIndex = 0;


	if (input->IsKeyDown(KeyCode::UP) || input->IsKeyDown(KeyCode::W))
	{
		velocity = foward * -5.5f;
		AnimationIndex = 1;
	}
	else if (input->IsKeyDown(KeyCode::DOWN) || input->IsKeyDown(KeyCode::S))
	{
		velocity = foward * 5.5f;
		AnimationIndex = 2;
	}
	else if (input->IsKeyDown(KeyCode::SPACE))
	{
		AnimationIndex = 3;
	}
	if (input->IsKeyDown(KeyCode::LEFT) || input->IsKeyDown(KeyCode::A))
	{
		velocity += right * 5.5f;
		AnimationIndex = 2;
	}
	else if (input->IsKeyDown(KeyCode::RIGHT) || input->IsKeyDown(KeyCode::D))
	{
		velocity += right * -5.5f;
		AnimationIndex = 2;
	}

	velocity.y = currentVelocity.y;
	
	mCharacterRigidBody->SetVelocity(velocity);

	if (AnimationIndex != mCurrentAnimationIndex)
	{
		//set animation
		mCurrentAnimationIndex = AnimationIndex;
		mCharacterAnimation->Play(mCurrentAnimationIndex, true);
	}
}

