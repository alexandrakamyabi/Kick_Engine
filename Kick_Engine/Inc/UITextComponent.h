#pragma once


#include "UIComponent.h"

namespace Kick_Engine
{
    class UITextComponent : public UIComponent
    {
    public:
        SET_TYPE_ID(ComponentId::UIText);

        void Initialize() override;
        void Terminate() override;
        void Render() override;
        void Deserialize(const rapidjson::Value& value) override;

    private:
        std::filesystem::path mText;
        Kick_Math::Vector2 mPosition = Kick_Math::Vector2::Zero;
        float mSize = 1.0f;
        Color mColor = Colors::Black;
    };
}