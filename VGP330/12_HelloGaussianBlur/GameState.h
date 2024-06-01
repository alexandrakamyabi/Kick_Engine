#pragma once
#include <Kick_Engine/Inc/Kick_Engine.h>

class GameState : public Kick_Engine::AppState
{
public:
	virtual void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

protected:
	Kick_Engine::Graphics::DirectionalLight mDirectionalLight;
	Kick_Engine::Graphics::Camera mCamera;
	
	//Effects
	Kick_Engine::Graphics::StandardEffect mStandardEffect;
	Kick_Engine::Graphics::PostProcessingEffect mPostProcessEffect;
	Kick_Engine::Graphics::GaussianBlurEffect mGaussianBlurEffect;

	//Objects
	Kick_Engine::Graphics::RenderGroup mCharacter;
	Kick_Engine::Graphics::RenderObject mGround;
	Kick_Engine::Graphics::RenderObject mScreenQuad;

	//Render Targets
	Kick_Engine::Graphics::RenderTarget mRenderTarget;
	Kick_Engine::Graphics::RenderTarget mBlurRenderTarget;
};