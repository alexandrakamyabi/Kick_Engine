#pragma once


namespace Kick_Engine
{
    class GameObject;
    class Component;

    using CustomMake = std::function<Component*(const std::string&, GameObject&)>;

    namespace GameObjectFactory
    {
        void SetCustomMake(CustomMake customMake);
        void Make(const std::filesystem::path& templatePath, GameObject& gameObject);
    }
}