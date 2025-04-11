#pragma once

#include <../Kick_Engine/Inc/Kick_Engine.h>
#include "TypeIds.h"

class CustomDebugDrawComponent : public Kick_Engine::Component
{
public:
    SET_TYPE_ID(CustomComponentId::CustomDebugDraw);

    void Initialize() override;
    void Terminate() override;

    void Update(float deltaTime) override;

    void AddDebugDraw();
    void Deserialize(const rapidjson::Value& value) override;

private:
    const Kick_Engine::TransformComponent* mTransformComponent;
    Kick_Engine::Kick_Math::Vector3 mPosition = Kick_Engine::Kick_Math::Vector3::Zero;
    Kick_Engine::Color mColor = Kick_Engine::Colors::Pink;
    uint32_t mSlices = 0;
    uint32_t mRings = 0;
    float mRadius = 0.0f;
};