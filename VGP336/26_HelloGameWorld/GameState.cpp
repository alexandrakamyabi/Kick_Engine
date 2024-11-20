#include "GameState.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Input;
using namespace Kick_Engine::Audio;
using namespace Kick_Engine::Physics;

#include "CustomDebugDrawComponent.h"
#include "CustomDebugDrawService.h"

Component* CustomComponentMake(const std::string& componentName, GameObject& gameObject)
{
	if (componentName == "CustomDebugDrawComponent")
	{
		return gameObject.AddComponent<CustomDebugDrawComponent>();
	}
	return nullptr;
}

Component* CustomComponentGet(const std::string& componentName, GameObject& gameObject)
{
	if (componentName == "CustomDebugDrawComponent")
	{
		return gameObject.GetComponent<CustomDebugDrawComponent>();
	}
	return nullptr;
}

Service* CustomServiceMake(const std::string& sercviceName, GameWorld& gameWorld)
{
	if (sercviceName == "CustomDebugDrawService")
	{
		return gameWorld.AddService<CustomDebugDrawService>();
	}
	return nullptr;
}

void GameState::Initialize()
{
	GameObjectFactory::SetCustomGet(CustomComponentGet);
	GameObjectFactory::SetCustomMake(CustomComponentMake);
	GameWorld::SetCustomService(CustomServiceMake);
	mGameWorld.LoadLevel(L"../../Assets/Templates/Level/testLevel.json");
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