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
	void RenderObject(); 
	Kick_Engine::Graphics::Camera mCamera;
	Kick_Engine::Graphics::MeshPX mMesh;

	Kick_Engine::Graphics::Texture mTexture;
	Kick_Engine::Graphics::Sampler mSampler;
	Kick_Engine::Graphics::RenderTarget mRenderTarget;
};