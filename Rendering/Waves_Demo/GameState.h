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
	Kick_Engine::Graphics::DirectionalLight m_DirectionalLight;
	Kick_Engine::Graphics::Camera m_Camera;

	Kick_Engine::Graphics::RenderObject m_Water;
	Kick_Engine::Graphics::WaveEffect m_WaveEffect;
};