#pragma once
#include <Kick_Engine/Inc/Kick_Engine.h>

class GameState : public Kick_Engine::AppState
{
	struct PlanetInfo
	{
		Vector3 position{};
		float orbitRadius{};
		float orbitTime{};
		float orbitMultiplier{};
		float orbitAngle{};
		float dayTime{};
		float dayMultiplier{};
		float rotationAngle{};
	};

public:
	virtual void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

protected:
	void CreateSkySphere(std::filesystem::path texturePath);
	void CreatePlanet(float planetRadius, float orbitRadius, float orbitTime, float dayTime, std::filesystem::path texturePath);
	void RenderPlanet(int i);
	void RenderPlanetImage(int i);

	Kick_Engine::Graphics::Camera mCamera;
	Kick_Engine::Graphics::Camera mCamera2;


	std::vector<Kick_Engine::Graphics::RenderTarget*> mRenderTargets;
	std::vector<Kick_Engine::Graphics::Texture*> mTextures;
	std::vector<PlanetInfo*> mInfo;
	Kick_Engine::Graphics::Sampler mSampler;

	size_t planetCount;
};