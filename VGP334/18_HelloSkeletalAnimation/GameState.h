#pragma once

#include <Kick_Engine/Inc/Kick_Engine.h>

class MainState : public Kick_Engine::AppState
{
public:
	void Initialize()  override;
	void Terminate()  override;
	void Update(const float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	void UpdateCameraControl(float deltaTime);

	Kick_Engine::Graphics::Camera mCamera;
	Kick_Engine::Graphics::DirectionalLight mDirectionalLight;
	Kick_Engine::Graphics::StandardEffect mStandardEffect;

	Kick_Engine::Graphics::RenderGroup mCharacter;
};