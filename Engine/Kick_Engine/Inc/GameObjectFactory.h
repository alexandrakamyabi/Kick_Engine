#pragma once

namespace Kick_Engine
{
	class GameObject;
	namespace GameObjectFactory
	{
		void Make(const std::filesystem::path& templatePath, GameObject& gameObject);
	}
}