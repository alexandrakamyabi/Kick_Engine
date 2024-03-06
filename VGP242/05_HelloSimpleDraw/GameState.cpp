#include "GameState.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
}

void GameState::Terminate()
{
}

void GameState::Update(float deltaTime)
{
	auto input = Input::InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}

	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	if (input->IsKeyPressed(KeyCode::SPACE))
	{
		MainApp().ChangeState(mNextStateName);
	}
}

void GameState::Render()
{
}

void DrawingState::Render()
{

	SimpleDraw::AddLine({ 1.0f, 0.0f, 0.5f }, { 0.0f, 2.0f, 0.0f }, Colors::Teal);
	SimpleDraw::AddLine({ -1.0f, 0.0f, 0.5f }, { 0.0f, 2.0f, 0.0f }, Colors::Teal);

	SimpleDraw::AddLine({ 1.0f, 0.0f, -0.5f }, { 0.0f, 2.0f, 0.0f }, Colors::Orange);
	SimpleDraw::AddLine({ -1.0f, 0.0f, -0.5f }, { 0.0f, 2.0f, 0.0f }, Colors::Orange);


	SimpleDraw::AddLine({ 1.0f, 0.0f, 0.5f }, { -1.0f, 0.0f, 0.5f }, Colors::Purple);
	SimpleDraw::AddLine({ -1.0f, 0.0f, 0.5f }, { -1.0f, 0.0f, -0.5f }, Colors::Purple);

	SimpleDraw::AddLine({ 1.0f, 0.0f, -0.5f }, { 1.0f, 0.0f, 0.5f }, Colors::Yellow);
	SimpleDraw::AddLine({ -1.0f, 0.0f, -0.5f }, { 1.0f, 0.0f, -0.5f }, Colors::Yellow);

	SimpleDraw::Render(mCamera);
}

void FilledAABBState::Render()
{
	SimpleDraw::AddFilledAABB(-Math::Vector3::One, Math::Vector3::One, Colors::DeepSkyBlue);
	SimpleDraw::Render(mCamera);
}

void AABBState::Render()
{
	SimpleDraw::AddAABB(-Math::Vector3::One, Math::Vector3::One, Colors::Lavender);
	SimpleDraw::Render(mCamera);
}

void SphereState::Render()
{
	SimpleDraw::AddSphere(60, 60, 1.0f, Colors::Lavender);
	SimpleDraw::Render(mCamera);
}

void TransformState::Render()
{
	SimpleDraw::AddTransform(Matrix4::Identity);
	SimpleDraw::Render(mCamera);
}
