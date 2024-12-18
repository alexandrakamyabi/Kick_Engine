#pragma once
#include <../Kick_Engine/Inc/Kick_Engine.h>
#include "TypeIds.h"

namespace Kick_Engine
{
	class CharacterControllerComponent : public Kick_Engine::Component
	{
	public:
		SET_TYPE_ID(ComponentId::CharacterController);

		void Initialize() override;
		void Terminate() override;
		void Update(float deltaTime) override;
	private:
		float mMovementSpeed = 0.0f;
		int mCurrentAnimationIndex = 0;
		Kick_Engine::AnimatorComponent* mCharacterAnimation = nullptr;
		Kick_Engine::RigidBodyComponent* mCharacterRigidBody = nullptr;
		Kick_Engine::TransformComponent* mCharacterTransform = nullptr;
	};
}
