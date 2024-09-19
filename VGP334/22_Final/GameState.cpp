#include "GameState.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Input;
using namespace Kick_Engine::Audio;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 3.0f, -10.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mDirectionalLight.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mDirectionalLight.specular = { 1.0f, 1.0f, 1.0f, 1.0f };

	mModelId = ModelManager::Get()->LoadModelId("../../Assets/Models/final/rin.model");
	//ModelManager::Get()->AddAnimation(mModelId, "../../Assets/Models/Animations/stepDance.animset");
	//ModelManager::Get()->AddAnimation(mModelId, "../../Assets/Models/Animations/waveDance.animset");
	//ModelManager::Get()->AddAnimation(mModelId, "../../Assets/Models/Animations/ymca.animset");
	mCharacter = CreateRenderGroup(mModelId, &mCharacterAnimator);
	mCharacterAnimator.Initialize(mModelId);

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFilePath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);
	mCharacterAnimator.PlayAnimation(0, true);
	mModelId2 = ModelManager::Get()->LoadModelId("../../Assets/Models/final/len.model");
	mCharacter2 = CreateRenderGroup(mModelId2, &mCharacterAnimator2);
	mCharacterAnimator2.Initialize(mModelId2);
	mCharacterAnimator2.PlayAnimation(0, true);
	SetRenderGroupPosition(mCharacter2, { 2.0f, 0.0f, 0.0f });
	SoundEffectManager* sem = SoundEffectManager::Get();
	mEventSoundIds.push_back(sem->Load("mikufiesta.wav"));
	sem->Play(mEventSoundIds[0], true);
	AnimationCallback cb = [&]() { sem->Play(mEventSoundIds[0]); };

	mEventAnimationTime = 0.0f;
	// Set up an animation that does not trigger any events or move the model
	mEventAnimation = AnimationBuilder()
		.AddPositionKey({ -2.0f, 0.0f, 0.0f }, 0.0f) // Keep the model stationary
		.Build();

	
}

void GameState::Terminate()
{
	mStandardEffect.Terminate();
	CleanupRenderGroup(mCharacter);
}

void GameState::Update(float deltaTime)
{
	mCharacterAnimator.Update(deltaTime);
	mCharacterAnimator2.Update(deltaTime);

#pragma region CameraMovement
	auto input = Input::InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}

	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}
#pragma endregion

	if (input->IsKeyPressed(KeyCode::SPACE))
	{
		SpacePressedEvent spacePressed;
		EventManager::Broadcast(&spacePressed);
	}

	//float prevTime = mEventAnimationTime;
	//mEventAnimationTime += deltaTime;
	//mEventAnimation.PlayEvents(prevTime, mEventAnimationTime);
	//while (mEventAnimationTime >= mEventAnimation.GetDuration())
	//{
	//	mEventAnimationTime -= mEventAnimation.GetDuration();
	//}
}

void GameState::Render()
{
	for (auto& ro : mCharacter)
	{
		ro.transform = mEventAnimation.GetTransform(mEventAnimationTime);
	}
	//for (auto& ro : mCharacter2)
	//{
	//	ro.transform = mEventAnimation.GetTransform(mEventAnimationTime);
	//}
	if (mDrawSkeleton)
	{
		Matrix4 transform = mCharacter[0].transform.GetMatrix4();
		AnimationUtil::BoneTransforms boneTransforms;
		AnimationUtil::ComputeBoneTransforms(mModelId, boneTransforms, &mCharacterAnimator);
		for (auto& boneTransform : boneTransforms)
		{
			boneTransform = boneTransform * transform;
		}
		AnimationUtil::DrawSkeleton(mModelId, boneTransforms);
	}

	SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(mCamera);

	if (!mDrawSkeleton)
	{
		mStandardEffect.Begin();
			DrawRenderGroup(mStandardEffect, mCharacter);
			DrawRenderGroup(mStandardEffect, mCharacter2);
		mStandardEffect.End();
	}
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.01f))
			{
				mDirectionalLight.direction = Math::Normalize(mDirectionalLight.direction);
			}

			ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
			ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
			ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
		}
		ImGui::Checkbox("DrawSkeleton", &mDrawSkeleton);
		if (ImGui::DragInt("Animation", &mAnimIndex, 1, -1, mCharacterAnimator.GetAnimationCount() - 1))
		{
			mCharacterAnimator.PlayAnimation(mAnimIndex, true);
		}
		mStandardEffect.DebugUI();
	ImGui::End();
}

void GameState::OnEvent2()
{
	SoundEffectManager::Get()->Play(mEventSoundIds[1]);
	AnimEvent animEvent;
	animEvent.eventName = "Shoot";
	EventManager::Broadcast(&animEvent);
}

void GameState::OnEvent3()
{
	SoundEffectManager::Get()->Play(mEventSoundIds[2]);
	AnimEvent animEvent;
	animEvent.eventName = "Explode";
	EventManager::Broadcast(&animEvent);
}

void GameState::OnSpaceEvent(const Kick_Engine::Event* event)
{
	LOG("SPACE EVENT OCCURED");
	SoundEffectManager::Get()->Play(mEventSoundIds[2]);
}

void GameState::OnAnimEvent(const Kick_Engine::Event* event)
{
	AnimEvent* eventData = (AnimEvent*)event;
	if (eventData->eventName == "Shoot")
	{
		LOG("SHOOT EVENT OCCURED");
	}
	else if (eventData->eventName == "Explode")
	{
		LOG("EXPLODE EVENT OCCURED");
	}
}
