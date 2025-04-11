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

	Kick_Engine::Graphics::ModelId mModelId;
	Kick_Engine::Graphics::RenderGroup mCharacter;
	Kick_Engine::Graphics::Animator mCharacterAnimator;
	Kick_Engine::Graphics::StandardEffect mStandardEffect;

	int mAnimIndex = -1;
	bool mDrawSkeleton = false;
};