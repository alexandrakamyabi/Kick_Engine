#include "GameState.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Input;
using namespace Kick_Engine::Audio;
using namespace Kick_Engine::Physics;

void GameState::Initialize()
{
	mGameWorld.AddService<CameraService>();
	mGameWorld.Initialize();

	GameObject* gameObject = mGameWorld.CreateGameObject("Transform");

	gameObject->AddComponent<TransformComponent>();
	gameObject->Initialize();

	GameObject* cameraGameObject = mGameWorld.CreateGameObject("Camera");

	CameraComponent* camera = cameraGameObject->AddComponent<CameraComponent>();
	cameraGameObject->AddComponent<FPSCameraComponent>();
	cameraGameObject->Initialize();
	camera->GetCamera().SetPosition({ 0.0f, 2.0f, -2.0 });
	camera->GetCamera().SetLookAt({ 0.0f, 0.0f, 0.0f });
}

void GameState::Terminate()
{
	mGameWorld.Terminate();
}

void GameState::Update(float deltaTime)
{
	mGameWorld.Update(deltaTime);
}

void GameState::Render()
{
	mGameWorld.Render();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		mGameWorld.DebugUI();
	ImGui::End();
}