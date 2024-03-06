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
	Kick_Engine::Graphics::Camera mCamera;

	float mSphereAlpha = 1.0f;
	float mSquareAlpha = 1.0f;
	Math::Vector3 mPosition = Math::Vector3::Zero;
};