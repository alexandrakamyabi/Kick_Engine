#pragma once

#include "Component.h"

namespace Kick_Engine
{
	class RigidBodyComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::RigidBody);

		void Initialize() override;
		void Terminate() override;
		void Deserialize(const rapidjson::Value& value);

		void SetPosition(const Kick_Math::Vector3& position);
		void SetVelocity(const Kick_Math::Vector3& velocity);
		void SetRotationVelocity(const Kick_Math::Vector3& velocity);
		Vector3 GetVelocity();
		Vector3 GetPosition();
	private:
		friend class PhysicsService;
		Physics::CollisionShape mCollisionShape;
		Physics::RigidBody mRigidBody;
		float mMass = -1.0f;
	};
}