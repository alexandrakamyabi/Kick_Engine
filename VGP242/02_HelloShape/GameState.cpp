#include "GameState.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Input;

void GameState::Initialize()
{
	//CreateShape();

	//GraphicsSystem::Get()->CreateTriangles(mVertices);

	//std::filesystem::path shaderFilePath = L"../../Assets/Shaders/DoSomething.fx";

	//GraphicsSystem::Get()->CreateShaders(shaderFilePath);
}

void GameState::Terminate()
{
	mVertices.clear();
}

void GameState::Update(float deltaTime)
{
}

void GameState::Render()
{
	//GraphicsSystem::Get()->Render(mVertices.size());
}

void GameState::CreateShape()
{

}

void TriangleState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::ONE))
	{
		MainApp().ChangeState("TriforceState");
	}
	else if (InputSystem::Get()->IsKeyPressed(KeyCode::TWO))
	{
		MainApp().ChangeState("ChaosEmrald");
	}
}

void TriangleState::CreateShape()
{
	//mVertices.push_back({ { -0.5f, 0.0f, 0.0f }, Colors::Red });
	//mVertices.push_back({ { 0.0f, 0.75f, 0.0f }, Colors::Green });
	//mVertices.push_back({ { 0.5f, 0.0f,  0.0f }, Colors::Blue });
}

void TriforceState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::ONE))
	{
		MainApp().ChangeState("FeeeshState");
	}
	else if (InputSystem::Get()->IsKeyPressed(KeyCode::TWO))
	{
		MainApp().ChangeState("TriangleState");
	}
}

void TriforceState::CreateShape() {

	//mVertices.push_back({ { -0.5f, -0.5f + 0.25f , 0.0f }, Colors::LavenderBlush });
	//mVertices.push_back({ { -0.25f, 0.0f + 0.25f, 0.0f }, Colors::MediumPurple });
	//mVertices.push_back({ { 0.0f, -0.5f + 0.25f, 0.0f }, Colors::Thistle });


	//mVertices.push_back({ { 0.0f, -0.5f + 0.25f, 0.0f }, Colors::Thistle });
	//mVertices.push_back({ { 0.25f, 0.0f + 0.25f, 0.0f }, Colors::MediumPurple });
	//mVertices.push_back({ { 0.5f, -0.5f + 0.25f, 0.0f }, Colors::LavenderBlush });


	//mVertices.push_back({ { -0.25f, 0.0f + 0.25f, 0.0f }, Colors::MediumPurple });
	//mVertices.push_back({ { 0.0f, 0.5f + 0.25f, 0.0f }, Colors::Plum });
	//mVertices.push_back({ { 0.25f, 0.0f + 0.25f, 0.0f }, Colors::MediumPurple });
}

void FeeeshState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::ONE))
	{
		MainApp().ChangeState("ChaosEmrald");
	}
	else if (InputSystem::Get()->IsKeyPressed(KeyCode::TWO))
	{
		MainApp().ChangeState("TriforceState");
	}
}
void FeeeshState::CreateShape()
{
	//mVertices.push_back({ { -0.2f, 0.0f, 0.0f }, Colors::RoyalBlue });
	//mVertices.push_back({ { -0.5f, -0.3f, 0.0f }, Colors::DodgerBlue });
	//mVertices.push_back({ { -0.5f, 0.3f, 0.0f }, Colors::DeepSkyBlue });

	//mVertices.push_back({ { -0.5f, 0.0f, 0.0f }, Colors::Pink });
	//mVertices.push_back({ { -0.6f, -0.1f, 0.0f }, Colors::LightPink });
	//mVertices.push_back({ { -0.6f, 0.1f, 0.0f }, Colors::White });
}

void ChaosEmrald::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::ONE))
	{
		MainApp().ChangeState("FeeeshState");
	}
	else if (InputSystem::Get()->IsKeyPressed(KeyCode::TWO))
	{
		MainApp().ChangeState("TriangleState");
	}
}

void ChaosEmrald::CreateShape() {

	//float yOffset = 0.25f;
	//
	//mVertices.push_back({ { 0.0f, 0.0f + yOffset, 0.0f }, Colors::Crimson });
	//mVertices.push_back({ { -0.5f, 0.0f + yOffset, 0.0f }, Colors::DeepSkyBlue });
	//mVertices.push_back({ { -0.25f, 0.25f + yOffset, 0.0f }, Colors::Gold });
	//
	//mVertices.push_back({ { 0.0f, 0.0f + yOffset, 0.0f }, Colors::Crimson });
	//mVertices.push_back({ { 0.25f, 0.25f + yOffset, 0.0f }, Colors::Gold });
	//mVertices.push_back({ { 0.5f, 0.0f + yOffset, 0.0f }, Colors::DeepSkyBlue });
	//
	//mVertices.push_back({ { 0.5f, 0.0f + yOffset, 0.0f }, Colors::DeepSkyBlue });
	//mVertices.push_back({ { 0.0f, -0.75f + yOffset, 0.0f }, Colors::Magenta });
	//mVertices.push_back({ { 0.0f, 0.0f + yOffset, 0.0f }, Colors::Crimson });
	//
	//mVertices.push_back({ { -0.5f, 0.0f + yOffset, 0.0f }, Colors::DeepSkyBlue });
	//mVertices.push_back({ { 0.0f, 0.0f + yOffset, 0.0f }, Colors::Crimson });
	//mVertices.push_back({ { 0.0f, -0.75f + yOffset, 0.0f }, Colors::Magenta });
	//
	//mVertices.push_back({ { -0.25f, 0.25f + yOffset, 0.0f }, Colors::Gold });
	//mVertices.push_back({ { 0.25f, 0.25f + yOffset, 0.0f }, Colors::Magenta });
	//mVertices.push_back({ { 0.0f, -0.75f + yOffset, 0.0f }, Colors::Crimson });
}