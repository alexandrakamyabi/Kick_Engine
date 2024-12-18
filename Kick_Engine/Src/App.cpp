#include "Precompiled.h"
#include "App.h"
#include "AppState.h"
#include "EventManager.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Core;
using namespace Kick_Engine::Input;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Physics;
using namespace Kick_Engine::Audio;

void App::ChangeState(const std::string& stateName)
{
    auto iter = mAppStates.find(stateName);
    if (iter != mAppStates.end())
    {
        mNextState = iter->second.get();
    }
}

void App::Run(const AppConfig& config)
{
    // create window
    Window myWindow;
    myWindow.Initialize(
        GetModuleHandle(nullptr),
        config.appName,
        config.winWidth,
        config.winHeight
    );

    ASSERT(myWindow.IsActive(), "Failed to create window!");

    
    // initialize static classes
    PhysicsWorld::Settings physicsSettings;

    auto handle = myWindow.GetWindowHandle();
    InputSystem::StaticInitialize(handle);
    GraphicsSystem::StaticInitialize(handle, false);
    DebugUI::StaticInitialize(handle, false, true);
    SimpleDraw::StaticInitialize(config.debugDrawLimit);
    TextureManager::StaticInitialize("../../Assets/Textures/");
    ModelManager::StaticInitialize();
    PhysicsWorld::StaticInitialize(physicsSettings);
    EventManager::StaticInitialize();
    AudioSystem::StaticInitialize();
    SoundEffectManager::StaticInitialize("../../Assets/Sounds");
    UISpriteRenderer::StaticInitialize();
    UIFont::StaticInitialize(UIFont::FontType::Arial);

    ASSERT(mCurrentState != nullptr, "App -- need an app state");
    mCurrentState->Initialize();
    mRunning = true;
    while (mRunning)
    {
        myWindow.ProcessMessage();

        auto inputSystem = InputSystem::Get();
        inputSystem->Update();


        if (!myWindow.IsActive() || inputSystem->IsKeyPressed(KeyCode::ESCAPE))
        {
            Quit();
            break;
        }

        if (mNextState != nullptr)
        {
            mCurrentState->Terminate();
            mCurrentState = std::exchange(mNextState, nullptr);
            mCurrentState->Initialize();
        }
        AudioSystem::Get()->Update();
        //run the game
        auto deltaTime = TimeUtil::GetDeltaTime();

        if (deltaTime < 0.5f)
        {
            // physics is a service
            //PhysicsWorld::Get()->Update(deltaTime);
            mCurrentState->Update(deltaTime);
        }

        auto gs = GraphicsSystem::Get();
        auto sr = UISpriteRenderer::Get();
        gs->BeginRender();
            sr->BeginRender();
                mCurrentState->Render();
            sr->EndRender();
            DebugUI::BeginRender();
                mCurrentState->DebugUI();
            DebugUI::EndRender();
        gs->EndRender();
    }

    mCurrentState->Terminate();

    //terminate static classes
    UIFont::StaticTerminate();
    UISpriteRenderer::StaticTerminate();
    SoundEffectManager::StaticTerminate();
    AudioSystem::StaticTerminate();
    EventManager::StaticTerminate();
    PhysicsWorld::StaticTerminate();
    ModelManager::StaticTerminate();
    TextureManager::StaticTerminate();
    SimpleDraw::StaticTerminate();
    DebugUI::StaticTerminate();
    InputSystem::StaticTerminate();
    GraphicsSystem::StaticTerminate();
    myWindow.Terminate();
}

void App::Quit()
{
    mRunning = false;
}
