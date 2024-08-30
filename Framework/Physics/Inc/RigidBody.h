#pragma once

#include "PhysicsObject.h"

namespace Kick_Engine::Physics
{
	class CollisionShape;

	class RigidBody final : public PhysicsObject
	{
	public:
		RigidBody() = default;
		~RigidBody() override;

		void Initialize(Kick_Engine::Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass = 0.0f);
		void Terminate();

		void SetPosition(const Kick_Engine::Math::Vector3& position);
		void SetVelocity(const Kick_Engine::Math::Vector3& position);

		bool IsDynamic() const;

	private: 
		void SyncGraphics() override;
		btRigidBody* GetRigidBody() override { return mRigidBody; }

		btRigidBody* mRigidBody = nullptr;
		btDefaultMotionState* mMotionState = nullptr;
		float mMass = 0.0f;

		Kick_Engine::Graphics::Transform* mGraphicsTransform = nullptr;
	};
}