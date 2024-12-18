#pragma once

#include "Component.h"

namespace Kick_Engine
{
    class CameraComponent final : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::Camera);

        void Initialize() override;
        void Deserialize(const rapidjson::Value& value) override;
        void Terminate() override;

        Graphics::Camera& GetCamera();
        const Graphics::Camera& GetCamera() const;

    private:
        Graphics::Camera mCamera;
    };
}