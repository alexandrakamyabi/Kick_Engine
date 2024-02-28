#pragma once
#include <Kick_Engine/Inc/Kick_Engine.h>

class GameState : public Kick_Engine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	Kick_Engine::Graphics::Camera mCamera;
	Kick_Engine::Graphics::MeshPC mMesh;

};