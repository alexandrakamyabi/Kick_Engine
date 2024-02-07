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
	virtual void CreateShape();

	using Vertices = std::vector<Kick_Engine::Graphics::Vertex>;
	Vertices mVertices;
};

class TriangleState : public GameState
{
public:
	void Update(float deltaTime) override;

private:
	void CreateShape() override;
};

class TriforceState : public GameState
{
public:
	void Update(float deltaTime) override;

private:
	void CreateShape() override;
};

class FeeeshState : public GameState
{
public:
	void Update(float deltaTime) override;

private:
	void CreateShape() override;
};

class ChaosEmrald : public GameState
{
public:
	void Update(float deltaTime) override;

private:
	void CreateShape() override;
};