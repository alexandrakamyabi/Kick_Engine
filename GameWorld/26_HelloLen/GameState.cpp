#include "GameState.h"

#include "CharacterControllerComponent.h"
#include "TPSCameraComponent.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Kick_Math;
using namespace Kick_Engine::Input;


namespace
{
    Component* CustomComponentMake(const std::string& componentName, GameObject& gameObject)
    {
        if (componentName == "CharacterControllerComponent")
        {
            return gameObject.AddComponent<CharacterControllerComponent>();
        }
        else if (componentName == "TPSCameraComponent")
        {
            return gameObject.AddComponent<TPSCameraComponent>();
        }
        return nullptr;
    }
    Service* CustomServiceMake(const std::string& serviceName, GameWorld& gameWorld)
    {
        return nullptr;
    }
}

void GameState::Initialize()
{
    GameObjectFactory::SetCustomMake(CustomComponentMake);
    GameWorld::SetCustomService(CustomServiceMake);
    mGameWorld.LoadLevel("../../Assets/Templates/Levels/test_gameworld.json");
}
void GameState::Terminate()                                                                                              
{
    mGameWorld.Terminate();
}
void GameState::Render()
{
    mGameWorld.Render();
}
void GameState::Update(float deltaTime)
{
    mGameWorld.Update(deltaTime);
}
void GameState::DebugUI()
{
    //SimpleDraw::AddGroundPlane(10.0f, Colors::White);
    ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        mGameWorld.DebugUI();
    ImGui::End();
}