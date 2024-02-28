#pragma once
#include <Kick_Engine/Inc/Kick_Engine.h>

class GameState : public Kick_Engine::AppState
{
public:
	virtual void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	virtual void CreateBuffer() = 0;
	virtual void CreateShader() = 0;

	Kick_Engine::Graphics::Camera mCamera;

	Kick_Engine::Graphics::Texture mTexture;
	Kick_Engine::Graphics::Sampler mSampler;
};

class CubeState : public GameState
{
public:
	void Update(float deltaTime) override;

protected:
	void CreateBuffer() override;
	void CreateShader() override;

private:
	Kick_Engine::Graphics::MeshPC mMesh;
};

class RectState : public GameState
{
public:
	void Update(float deltaTime) override;

protected:
	void CreateBuffer() override;
	void CreateShader() override;

private:
	Kick_Engine::Graphics::MeshPC mMesh;
};

class PlaneState : public GameState
{
public:
	void Update(float deltaTime) override;

protected:
	void CreateBuffer() override;
	void CreateShader() override;

private:
	Kick_Engine::Graphics::MeshPC mMesh;
};

class SphereState : public GameState
{
public:
	void Update(float deltaTime) override;

protected:
	void CreateBuffer() override;
	void CreateShader() override;

private:
	Kick_Engine::Graphics::MeshPC mMesh;
};

class CylinderState : public GameState
{
public:
	void Update(float deltaTime) override;

protected:
	void CreateBuffer() override;
	void CreateShader() override;

private:
	Kick_Engine::Graphics::MeshPC mMesh;
};

class SkyBoxState : public GameState
{
public:
	void Update(float deltaTime) override;

protected:
	void CreateBuffer() override;
	void CreateShader() override;

private:
	Kick_Engine::Graphics::MeshPX mMesh;
};															   
															   
class SkySphereState : public GameState						   
{
public:
	void Update(float deltaTime) override;

protected:
	void CreateBuffer() override;
	void CreateShader() override;

private:
	Kick_Engine::Graphics::MeshPX mMesh;
};