#include "GameState.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Kick_Math;
using namespace Kick_Engine::Input;

void GameState::Initialize()
{
    CameraService* cs = mGameWorld.AddService<CameraService>();
    mGameWorld.AddService<UpdateService>();
    mGameWorld.AddService<RenderService>();
    mGameWorld.Initialize(50);

    mGameWorld.CreateGameObject("../../Assets/Templates/fps_camera.json", "Camera");
    mGameWorld.CreateGameObject("../../Assets/Templates/test_model.json", "Obj");
};
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
    SimpleDraw::AddGroundPlane(10.0f, Colors::White);
    ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        mGameWorld.DebugUI();
    ImGui::End();
}